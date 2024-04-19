//
// Created by legion on 2024/4/16.
//

#include "CompilationEngine.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <common.h>
#include <vector>
#include <algorithm>

using std::cerr;
using std::endl;
using std::cout;
using std::getline;
using std::istringstream;
using std::setw;
using std::setfill;

CompilationEngine::CompilationEngine(string input_filename, string output_filename) {
    this->input_filename = input_filename;
    this->output_filename = output_filename;
    input.open(input_filename, std::ios::binary);
    if (!input.is_open()) {
        cerr << "Compilation Engine could not open file " << input_filename << endl;
        exit(1);
    }
    output.open(output_filename, std::fstream::out | std::fstream::trunc | std::ios::binary);
    if (!output.is_open()) {
        cerr << "Compilation Engine could not output file " << output_filename << endl;
        exit(1);
    }
}

void CompilationEngine::compile_class() {
    write_nonterminal("class");

    // get rid of <token>
    getline(input, line);
    if (line.find("<tokens>") == string::npos) {
        std::cerr << "Syntax analysis failed: the first line of " << input_filename << " is not <token>" << endl;
        exit(1);
    }

    // class (keyword)
    next_line();
    ret = check_token_valid("keyword", "class");
    if (ret == -1) {
        cerr << "Expecting <keyword> class </keyword> but there's not." << endl;
        exit(1);
    }
    stringbuf_clear();

    // className (identifier)
    next_line();
    ret = check_token_valid("identifier");
    if (ret == -1) {
        cerr << "Expecting <identifier> className </identifier> but there's not." << endl;
        exit(1);
    }
    stringbuf_clear();

    // { (symbol)
    next_line();
    ret = check_token_valid("symbol", "{");
    if (ret == -1) {
        cerr << "Expecting <symbol> { </symbol> but there's not." << endl;
        exit(1);
    }
    stringbuf_clear();

    // record the read header
    do {
        read_header = input.tellg();
        // classVardec (call compile_class_var_dec)
        ret = compile_class_var_dec();
    } while (ret != -1);
    input.seekg(read_header, std::ios_base::beg);

    do {
        read_header = input.tellg();
        // classroutinedec (call compile_subroutine)
        ret = compile_subroutine();
    } while (ret != -1);
    input.seekg(read_header, std::ios_base::beg);

    // } (symbol)
    next_line();
    ret = check_token_valid("symbol", "}");
    if (ret == -1) {
        cerr << "No closing } for class declaration" << endl;
        exit(1);
    }
    stringbuf_clear();

    // get rid of </token>
    getline(input, line);
    if (line.find("</tokens>") == string::npos) {
        std::cerr << "Parsing failed: the last line of " << input_filename << " is not </tokens>" << endl;
        exit(1);
    }
    write_close_nonterminal("class");
}

int CompilationEngine::compile_class_var_dec() {
    write_nonterminal("classVarDec");

    // static / field
    next_line();

    ret = check_token_valid("keyword", "static | field");
    if (ret == -1) {
        cerr << "Static/field not found in variable declaration" << endl;
        is.clear();
        write_close_nonterminal("classVarDec");
        return -1;
    }
    stringbuf_clear();

    // type
    next_line();
    ret = compile_type();
    if (ret == -1) {
        cerr << "Variable type invalid" << endl;
        exit(1);
    }
    stringbuf_clear();

    // varName
    next_line();
    if (check_token_valid("identifier") == -1) {
        cerr << "Variable name is not of type identifier" << endl;
        exit(1);
    }
    stringbuf_clear();

    // 0 or more ,varName
    do {
        // record the read header
        read_header = input.tellg();
        // ,
        next_line();
        ret = check_token_valid("symbol", ",");
        if (ret != -1) {
            stringbuf_clear();

            // varName
            next_line();
            ret = check_token_valid("identifier");
            if (ret == -1) {
                cerr << "No invalid varName detected." << endl;
                exit(1);
            }
            stringbuf_clear();
        }
    } while (ret != -1);
    input.seekg(read_header, std::ios_base::beg);

    // ;
    next_line();
    ret = check_token_valid("symbol", ";");
    if (ret == -1) {
        cerr << "No ; symbol detected in the end of variable declaration" << endl;
        exit(1);
    }
    stringbuf_clear();

    write_close_nonterminal("classVarDec");
    return 0;
}

int CompilationEngine::compile_subroutine() {
    write_nonterminal("subroutineDec");

    // constructor | function | method(keyword)
    next_line();
    ret = check_token_valid("keyword", "constructor | function | method");
    if (ret == -1) {
        cerr << "Expecting constructor | function | method in subroutine declaration" << endl;
        is.clear();
        write_close_nonterminal("subroutineDec");
        return -1;
    }
    stringbuf_clear();

    // void(keyword) | type
    next_line();
    if (check_token_valid("keyword", "void") == -1 && compile_type() == -1) {
        cerr << "subroutine return type invalid." << endl;
        exit(1);
    }
    stringbuf_clear();

    // subroutine_name(identifier)
    next_line();
    ret = check_token_valid("identifier");
    if (ret == -1) {
        cerr << "Expecting subroutine name is an identifier" << endl;
        exit(1);
    }
    stringbuf_clear();

    // ( (symbol)
    next_line();
    ret = check_token_valid("symbol", "(");
    if (ret == -1) {
        cerr << "Expecting ( before subroutine parameter list" << endl;
        exit(1);
    }
    stringbuf_clear();

    // parameter_list
    compile_parameter_list();

    // ) (symbol)
    next_line();
    ret = check_token_valid("symbol", ")");
    if (ret == -1) {
        cerr << "Expecting ) after subroutine parameter list" << endl;
        exit(1);
    }
    stringbuf_clear();

    // subroutine_body
    compile_subroutine_body();

    write_close_nonterminal("subroutineDec");
    return 0;
}

int CompilationEngine::compile_parameter_list() {
    write_nonterminal("parameterList");
    output << os.str();
    os.str("");
    os.clear();

    // record the read header
    read_header = input.tellg();

    // type
    next_line();
    ret = compile_type();
    if (ret == -1) {
        cerr << "There's no parameter list." << endl;
        input.seekg(read_header, std::ios_base::beg);
        is.clear();
        ret = 0;
        write_close_nonterminal("parameterList");
        return 0;
    }
    stringbuf_clear();

    // varName
    next_line();
    ret = check_token_valid("identifier");
    if (ret == -1) {
        cerr << "Invalid parameter list: no varName as identifier." << endl;
        exit(1);
    }
    stringbuf_clear();

    // (, type varName)*
    do {
        read_header = input.tellg();
        // , (symbol)
        next_line();
        ret = check_token_valid("symbol", ",");
        if (ret == -1) {
            std::cerr << "There's only one parameter in the parameter list." << endl;
            is.clear();
            break;
        }
        stringbuf_clear();

        // type
        next_line();
        ret = compile_type();
        if (ret == -1) {
            std::cerr << "There's an invalid type in the parameter list" << endl;
            exit(1);
        }
        stringbuf_clear();

        // varName
        next_line();
        ret = check_token_valid("identifier");
        if (ret == -1) {
            std::cerr << "There's an invalid varName in the parameter list." << endl;
            exit(1);
        }
        stringbuf_clear();
    } while (ret != -1);
    input.seekg(read_header, std::ios_base::beg);

    ret = 0;

    write_close_nonterminal("parameterList");
    return 0;
}

int CompilationEngine::compile_subroutine_body() {
    write_nonterminal("subroutineBody");
    output << os.str();
    os.str("");
    os.clear();

    // {
    next_line();
    ret = check_token_valid("symbol", "{");
    if (ret == -1) {
        std::cerr << "{ missing in the subroutine body." << endl;
        exit(1);
    }
    stringbuf_clear();

    // varDec*
    do {
        read_header = input.tellg();
        ret = compile_var_dec();
    } while (ret != -1);
    input.seekg(read_header, std::ios_base::beg);

    // statements
    compile_statements();

    // }
    next_line();
    ret = check_token_valid("symbol", "}");
    if (ret == -1) {
        std::cerr << "} missing in the subroutine body." << endl;
        exit(1);
    }
    stringbuf_clear();

    write_close_nonterminal("subroutineBody");
    return 0;
}

int CompilationEngine::compile_var_dec() {
    write_nonterminal("varDec");
    // var
    next_line();
    ret = check_token_valid("keyword", "var");
    if (ret == -1) {
        cerr << "There's no var keyword in variable declaration, compile_var_dec() failed." << endl;
        is.clear();
        write_close_nonterminal("varDec");
        return -1;
    }
    stringbuf_clear();

    // type
    next_line();
    ret = compile_type();
    if (ret == -1) {
        cerr << "There's an invalid type in variable declaration, compile_var_dec() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // varName
    next_line();
    ret = check_token_valid("identifier");
    if (ret == -1) {
        cerr << "Variable name is not an identifier, compile_var_dec() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // (',' varName)*
    do {
        read_header = input.tellg();
        // ,
        next_line();
        ret = check_token_valid("symbol", ",");
        if (ret != -1) {
            stringbuf_clear();

            // varName
            next_line();
            ret = check_token_valid("identifier");
            if (ret == -1) {
                cerr << "No varName in the var dec, compile_var_dec() failed.";
                exit(1);
            }
            stringbuf_clear();
        }
    } while (ret != -1);
    input.seekg(read_header, std::ios_base::beg);

    // ;
    next_line();
    ret = check_token_valid("symbol", ";");
    if (ret == -1) {
        cerr << "No ; detected in the end of variable declaration, compile_ver_dec() failed." << endl;
        exit(1);
    }
    stringbuf_clear();
    write_close_nonterminal("varDec");
    return 0;
}

int CompilationEngine::compile_statements() {
    write_nonterminal("statements");
    output << os.str();
    os.str("");
    os.clear();

    // statement*
    do {
        // record the read_header
        read_header = input.tellg();
        ret = compile_statement();
    } while (ret != -1);
    input.seekg(read_header, std::ios_base::beg);

    ret = 0;

    write_close_nonterminal("statements");
    return 0;
}

int CompilationEngine::compile_statement() {
    //  letStatement
    read_header = input.tellg();
    ret = compile_let();
    if (ret == 0) {
        return 0;
    }
    input.seekg(read_header, std::ios_base::beg);

    //  ifStatement
    read_header = input.tellg();
    ret = compile_if();
    if (ret == 0) {
        return 0;
    }
    input.seekg(read_header, std::ios_base::beg);

    //  whileStatement
    read_header = input.tellg();
    ret = compile_while();
    if (ret == 0) {
        return 0;
    }
    input.seekg(read_header, std::ios_base::beg);

    //  doStatement
    read_header = input.tellg();
    ret = compile_do();
    if (ret == 0) {
        return 0;
    }
    input.seekg(read_header, std::ios_base::beg);

    //  returnStatement
    read_header = input.tellg();
    ret = compile_return();
    if (ret == 0) {
        return 0;
    }
    input.seekg(read_header, std::ios_base::beg);

    return ret;
}

int CompilationEngine::compile_do() {
    write_nonterminal("doStatement");

    // 'do'
    next_line();
    ret = check_token_valid("keyword", "do");
    if (ret == -1) {
        cerr << "There's no keyword do in do statement, compile_do() failed." << endl;
        is.clear();
        write_close_nonterminal("doStatement");
        return -1;
    }
    stringbuf_clear();

    // subroutineCall
    compile_subroutine_call();

    // ';'
    next_line();
    ret = check_token_valid("symbol", ";");
    if (ret == -1) {
        cerr << "No ; detected in the end of do statement, compile_do() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    write_close_nonterminal("doStatement");
    return 0;
}

int CompilationEngine::compile_let() {
    write_nonterminal("letStatement");

    // 'let'
    next_line();
    ret = check_token_valid("keyword", "let");
    if (ret == -1) {
        cerr << "There's no keyword let in do statement, compile_let() failed." << endl;
        write_close_nonterminal("letStatement");
        return -1;
    }
    stringbuf_clear();

    // varName
    next_line();
    ret = check_token_valid("identifier");
    if (ret == -1) {
        cerr << "There's no identifier varName in let statement, compile_let() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // ('[' expression ']')?
    read_header = input.tellg();
    // [
    next_line();
    ret = check_token_valid("symbol", "[");
    if (ret == -1) {
        is.clear();
        input.seekg(read_header, std::ios_base::beg);
    } else {
        stringbuf_clear();

        // expression
        compile_expression();

        // ]
        next_line();
        ret = check_token_valid("symbol", "]");
        if (ret == -1) {
            cerr << "Expecting ] symbol in let statement, compile_let() failed." << endl;
            exit(1);
        }
        stringbuf_clear();
    }

    // '='
    next_line();
    ret = check_token_valid("symbol", "=");
    if (ret == -1) {
        cerr << "There's no = symbol in let statement, compile_let() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // expression
    compile_expression();

    // ';'
    next_line();
    ret = check_token_valid("symbol", ";");
    if (ret == -1) {
        cerr << "There's no ; symbol in the end of let statement, compile_let() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    write_close_nonterminal("letStatement");
    return 0;
}

int CompilationEngine::compile_while() {
    write_nonterminal("whileStatement");

    // 'while'
    next_line();
    ret = check_token_valid("keyword", "while");
    if (ret == -1) {
        cerr << "There's no while keyword in while statement, compile_while() failed." << endl;
        is.clear();
        write_close_nonterminal("whileStatement");
        return -1;
    }
    stringbuf_clear();

    // '('
    next_line();
    ret = check_token_valid("symbol", "(");
    if (ret == -1) {
        cerr << "There's no symbol ( in while statement, compile_while() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // expression
    compile_expression();

    // ')'
    next_line();
    ret = check_token_valid("symbol", ")");
    if (ret == -1) {
        cerr << "There's no symbol ) in while statement, compile_while() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // '{'
    next_line();
    ret = check_token_valid("symbol", "{");
    if (ret == -1) {
        cerr << "There's no symbol { in while statement, compile_while() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // statements
    compile_statements();

    // '}'
    next_line();
    ret = check_token_valid("symbol", "}");
    if (ret == -1) {
        cerr << "There's no symbol } in the end of while statement, compile_while() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    write_close_nonterminal("whileStatement");
    return 0;
}

int CompilationEngine::compile_return() {
    write_nonterminal("returnStatement");

    // 'return'
    next_line();
    ret = check_token_valid("keyword", "return");
    if (ret == -1) {
        cerr << "There's no return statement" << endl;
        is.clear();
        write_close_nonterminal("returnStatement");
        return -1;
    }
    stringbuf_clear();

    // expression?
    read_header = input.tellg();
    ret = compile_expression();
    if (ret == -1) {
        input.seekg(read_header, std::ios_base::beg);
    }

    // ';'
    next_line();
    ret = check_token_valid("symbol", ";");
    if (ret == -1) {
        cerr << "There's no symbol ; in return statement, compile_return() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    write_close_nonterminal("returnStatement");
    return 0;
}

int CompilationEngine::compile_if() {
    write_nonterminal("ifStatement");

    // 'if'
    next_line();
    ret = check_token_valid("keyword", "if");
    if (ret == -1) {
        cerr << "There's no keyword if in if statement, compile_if() failed." << endl;
        write_close_nonterminal("ifStatement");
        return -1;
    }
    stringbuf_clear();

    // '('
    next_line();
    ret = check_token_valid("symbol", "(");
    if (ret == -1) {
        cerr << "There's no symbol ( in if statement, compile_if() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // expression
    compile_expression();

    // ')'
    next_line();
    ret = check_token_valid("symbol", ")");
    if (ret == -1) {
        cerr << "There's no symbol ) in if statement, compile_if() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // '{'
    next_line();
    ret = check_token_valid("symbol", "{");
    if (ret == -1) {
        cerr << "There's no symbol { in if statement, compile_if() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // statements
    compile_statements();

    // '}'
    next_line();
    ret = check_token_valid("symbol", "}");
    if (ret == -1) {
        cerr << "There's no symbol } in if statement, compile_if() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // ('else' '{' statements '}')?
    read_header = input.tellg();
    // else
    next_line();
    ret = check_token_valid("keyword", "else");
    if (ret == -1) {
        input.seekg(read_header, std::ios_base::beg);
        is.clear();
    } else {
        stringbuf_clear();

        // {
        next_line();
        ret = check_token_valid("symbol", "{");
        if (ret == -1) {
            cerr << "There's no symbol { in if statement, compile_if() failed." << endl;
            exit(1);
        }
        stringbuf_clear();

        // statements
        compile_statements();

        // }
        next_line();
        ret = check_token_valid("symbol", "}");
        if (ret == -1) {
            cerr << "There's no symbol } in if statement, compile_if() failed." << endl;
            exit(1);
        }
        stringbuf_clear();
    }

    ret = 0;
    write_close_nonterminal("ifStatement");
    return 0;
}

int CompilationEngine::compile_expression() {
    write_nonterminal("expression");
//    output << os.str();
//    os.str("");

    // term
    ret = compile_term();
    if (ret == -1) {
        is.clear();
        write_close_nonterminal("expression");
        return -1;
    }

    // (op term)*
    do {
        read_header = input.tellg();
        ret = compile_op();
        if (ret != -1) {
            ret = compile_term();
            if (ret == -1) {
                cerr << "No term after op in (op term)*, compile_expression() failed." << endl;
                break;
            }
        }
    } while (ret != -1);
    input.seekg(read_header, std::ios_base::beg);

    ret = 0;

    write_close_nonterminal("expression");
    return 0;
}

int CompilationEngine::compile_term() {
    write_nonterminal("term");

    // integerConstant |
    read_header = input.tellg();
    next_line();
    ret = check_token_valid("integerConstant");
    if (ret != -1) {
        stringbuf_clear();
        write_close_nonterminal("term");
        return 0;
    }
    is.clear();
    input.seekg(read_header, std::ios_base::beg);

    // stringConstant |
    read_header = input.tellg();
    next_line();
    ret = check_token_valid("stringConstant");
    if (ret != -1) {
        stringbuf_clear();
        write_close_nonterminal("term");
        return 0;
    }
    is.clear();
    input.seekg(read_header, std::ios_base::beg);

    // keywordConstant |
    read_header = input.tellg();
    ret = compile_keyword_constant();
    if (ret != -1) {
        write_close_nonterminal("term");
        return 0;
    }
    is.clear();
    input.seekg(read_header, std::ios_base::beg);

    // subroutineCall |
    read_header = input.tellg();
    ret = compile_subroutine_call();
    if (ret != -1) {
        write_close_nonterminal("term");
        return 0;
    }
    is.clear();
    input.seekg(read_header, std::ios_base::beg);

    // '(' expression ')' |
    read_header = input.tellg();
    // (
    next_line();
    ret = check_token_valid("symbol", "(");
    if (ret == -1) {
        cerr << "No symbol ( detected in term" << endl;
        is.clear();
        input.seekg(read_header, std::ios_base::beg);
    } else {
        stringbuf_clear();

        // expression
        ret = compile_expression();
        if (ret == -1) {
            cerr << "No expression detected in `( expression )`" << endl;
            is.clear();
            input.seekg(read_header, std::ios_base::beg);
        } else {
            // )
            next_line();
            ret = check_token_valid("symbol", ")");
            if (ret == -1) {
                cerr << "No symbol ) detected in `( expression )`" << endl;
                is.clear();
                input.seekg(read_header, std::ios_base::beg);
            } else {
                stringbuf_clear();
                write_close_nonterminal("term");
                return 0;
            }
        }
    }

    // unaryOp term
    read_header = input.tellg();
    ret = compile_unary_op();
    if (ret != -1) {
        ret = compile_term();
        if (ret != -1) {
            write_close_nonterminal("term");
            return 0;
        }
        cerr << "Term not existed in uaryOp term" << endl;
        exit(1);
    }
    is.clear();
    input.seekg(read_header, std::ios_base::beg);

    // varName |
    read_header = input.tellg();
    next_line();
    ret = check_token_valid("identifier");
    if (ret != -1) {
        stringbuf_clear();

        // varName '[' expression ']' |
        read_header = input.tellg();
        // [
        next_line();
        ret = check_token_valid("symbol", "[");
        if (ret != -1) {
            stringbuf_clear();

            // expression
            ret = compile_expression();
            if (ret != -1) {
                is.clear();

                // ]
                next_line();
                ret = check_token_valid("symbol", "]");
                if (ret == -1) {
                    cerr << "Expecting symbol ] in varName [ expression ], compile_term() failed." << endl;
                    exit(1);
                }
                stringbuf_clear();
            } else {
                cerr << "Expecting expression in varName [ expression ], compile_term() failed." << endl;
                exit(1);
            }
        } else {
            input.seekg(read_header, std::ios_base::beg);
            is.clear();
            ret = 0;
        }
        write_close_nonterminal("term");
        return 0;
    }

    write_close_nonterminal("term");
    return -1;
}

int CompilationEngine::compile_subroutine_call() {
    // subroutineName '(' expressionList ')' |
    read_header = input.tellg();
    // subroutineName
    next_line();
    ret = check_token_valid("identifier");
    if (ret == -1) {
        input.seekg(read_header, std::ios_base::beg);
        is.clear();
    } else {
        string iden = line;

        // (
        next_line();
        ret = check_token_valid("symbol", "(");
        if (ret == -1) {
            cerr << "Expecting ( in `subroutineName ( expressionList )`, compile_subroutine_call() failed." << endl;
            input.seekg(read_header, std::ios_base::beg);
            is.clear();
        } else {
            os << iden << endl;
            is.clear();
            stringbuf_clear();

            // expressionList
            ret = compile_expression_list();
            if (ret == -1) {
                cerr
                        << "Expecting expressionList in `subroutineName ( expressionList )`, compile_subroutine_call() failed."
                        << endl;
                exit(1);
            }

            // )
            next_line();
            ret = check_token_valid("symbol", ")");
            if (ret == -1) {
                cerr << "Expecting ) in `subroutineName ( expressionList )`, compile_subroutine_call() failed." << endl;
                exit(1);
            }
            stringbuf_clear();
            return 0;
        }
    }

    // (className | varName)
    next_line();
    ret = check_token_valid("identifier");
    if (ret == -1) {
        cerr
                << "Expecting className or varName in subroutine_call, but no identifier found, compile_subroutine_call() failed."
                << endl;
        return -1;
    }
    string iden = line;
    is.clear();

    // '.'
    next_line();
    ret = check_token_valid("symbol", ".");
    if (ret == -1) {
        cerr << "No symbol . in subroutine call, compile_subroutine_call() failed." << endl;
        return -1;
    }
    if (ret != -1) {
        os << iden << endl;
    }
    stringbuf_clear();

    // subroutineName
    next_line();
    ret = check_token_valid("identifier");
    if (ret == -1) {
        cerr
                << "Expecting subroutineName in subroutine_call, but no identifier found, compile_subroutine_call() failed."
                << endl;
        exit(1);
    }
    stringbuf_clear();

    // '('
    next_line();
    ret = check_token_valid("symbol", "(");
    if (ret == -1) {
        cerr << "Expecting symbol ( in subroutine_call, compile_subroutine_call() failed." << endl;
        exit(1);
    }
    stringbuf_clear();

    // expressionList
    ret = compile_expression_list();
    if (ret == -1) {
        cerr << "No expression list found in subroutine_call, compile_subroutine_call() failed." << endl;
        exit(1);
    }

    // ')'
    next_line();
    ret = check_token_valid("symbol", ")");
    if (ret == -1) {
        cerr << "No symbol ) in subroutine_call, compile_subroutine_call() failed." << endl;
        exit(1);
    }
    stringbuf_clear();
    return 0;
}

int CompilationEngine::compile_expression_list() {
    write_nonterminal("expressionList");
    output << os.str();
    os.str("");
    os.clear();

    // (expression (',' expression)* )?
    read_header = input.tellg();
    ret = compile_expression();
    if (ret == -1) {
        input.seekg(read_header, std::ios_base::beg);
        is.clear();
    } else {
        do {
            read_header = input.tellg();
            // ,
            next_line();
            ret = check_token_valid("symbol", ",");
            if (ret != -1) {
                stringbuf_clear();

                // expression
                ret = compile_expression();
                if (ret == -1) {
                    cerr << "Expecting expression in (, expression)*, compile_expression_list() failed." << endl;
                    exit(1);
                }
            }
        } while (ret != -1);
        input.seekg(read_header, std::ios_base::beg);
        is.clear();
    }

    ret = 0;
    write_close_nonterminal("expressionList");
    return 0;
}

int CompilationEngine::compile_op() {
    // '+'|'-'|'*'|'/'|'&'|'|'|'<'|'>'|'='
    next_line();
    ret = check_op("symbol");
    if (ret == -1) {
        is.clear();
        return -1;
    }
    stringbuf_clear();
    return 0;
}

int CompilationEngine::compile_unary_op() {
    // '-'|'~'
    next_line();
    ret = check_token_valid("symbol", " - ~");
    if (ret == -1) {
        is.clear();
        return -1;
    }
    stringbuf_clear();
    return 0;
}

int CompilationEngine::compile_keyword_constant() {
    //  'true'|'false'|'null'|'this'
    next_line();
    ret = check_token_valid("keyword", "true false null this");
    if (ret == -1) {
        is.clear();
        return -1;
    }
    stringbuf_clear();
    return 0;
}

void CompilationEngine::next_line() {
    getline(input, line);
    is.str(line);
    is >> tag >> word >> closingtag;
}

void CompilationEngine::stringbuf_clear() {
    cout.clear();
    os << line << endl;
    output << os.str();
    os.str("");
    os.clear();
    is.clear();
}

int CompilationEngine::check_token_valid(const string &token_type, const string &token) {
    if (tag.find(token_type) == string::npos) {
        is.clear();
        cout.clear();
        return -1;
    }
    if (!token.empty() && token.find(word) == string::npos) {
        is.clear();
        cout.clear();
        return -1;
    }
    return 0;
}

int CompilationEngine::check_op(const string &token_type) {
    std::vector<string> ops = {"+", "-", "*", "/", "&amp;", "|", "&lt;", "&gt;", "="};
    if (tag.find(token_type) == string::npos) {
        is.clear();
        cout.clear();
        return -1;
    }
    if (std::find(ops.begin(), ops.end(), word) == ops.end()) {
        is.clear();
        cout.clear();
        return -1;
    }
    return 0;
}

int CompilationEngine::compile_type() {
    // type: int char boolean(keyword) | className(identifier)
    // TODO: check if className valid
    if (check_token_valid("keyword", "int | char | boolean") == -1 && check_token_valid("identifier") == -1) {
        is.clear();
        cout.clear();
        return -1;
    }
    return 0;
}

void CompilationEngine::write_nonterminal(const string &non_terminal) {
    cout.clear();
//    os.write("  ", indent);
    os << "<" << non_terminal << ">" << endl;
    indent += 1;
}

void CompilationEngine::write_close_nonterminal(const string &non_terminal) {
    cout.clear();
    indent -= 1;
//    os.write("  ", indent);
    os << "</" << non_terminal << ">" << endl;
    if (ret != -1) {
        output << os.str();
    }
    os.str("");
    os.clear();
}
