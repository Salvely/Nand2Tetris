//
// Created by legion on 2024/4/20.
//

#include "CodeGen.h"
#include <iostream>
#include "common.h"

using std::cout;
using std::cerr;
using std::endl;
using boost::property_tree::ptree;

CodeGen::CodeGen(string input_filename, string output_filename) : writer(input, output) {
    input.open(input_filename);
    if (!input.is_open()) {
        cerr << "CodeGen: Input file " << input_filename << " open failed." << endl;
        exit(1);
    }

    output.open(output_filename);
    if (!output.is_open()) {
        cerr << "CodeGen: Output file " << output_filename << " open failed." << endl;
        exit(1);
    }

    read_xml(input, xml_tree);

    field_num = 0;
    local_num = 0;
}

void CodeGen::generate_class() {
    string data;
    // parse the class tree
    for (const ptree::value_type &p: xml_tree.get_child("class")) {
        data = p.second.data();
        boost::trim(data);
        // 'class'
        // className
        if (p.first == "identifier") {
            className = data;
            class_type.push_back(className);
        }
            // '{'
        else if (p.first == "symbol" && data == "{") {
            st.start_class();
        }
            // classVarDec*
        else if (p.first == "classVarDec") {
            generate_class_var_dec(p.second);
        }
            // subroutineDec*
        else if (p.first == "subroutineDec") {
            generate_subroutine_dec(p.second);
        }
            // '}'
        else if (p.first == "symbol" && data == "}") {
            writer.close();
        }
    }
}

void CodeGen::generate_class_var_dec(const pt &class_var_dec_tree) {
    // parse the classVarDec tree
    string kind;
    string type;
    string name;

    string data;
    for (auto &p: class_var_dec_tree) {
        data = p.second.data();
        boost::trim(data);

        //  ('static'|'field')
        if (p.first == "keyword" && (data == "static" || data == "field")) {
            if (data == "field") {
                kind = "this";
            } else {
                kind = data;
            }
        }
            //  type
        else if ((p.first == "keyword" &&
                  (data == "int" || data == "char" || data == "boolean")) ||
                 (p.first == "identifier" &&
                  (data == className || std::find(class_type.begin(), class_type.end(), data) != class_type.end()))) {
            type = data;
        }
            //  varName
        else if (p.first == "identifier") {
            name = data;
            st.define(name, type, kind);
            field_num += 1;
        }
            //  ';'
        else if (p.first == "symbol" && data == ";") {
            return;
        }
    }
}

void CodeGen::generate_subroutine_dec(const pt &subroutine_dec_tree) {
    /**
     * subroutine define process:
     * function function_name arg_num（generate_parameter_list()中写，因为需要计算参数的个数）
     *
     * return（generate_subroutine_body()中写）
     */
    st.start_subroutine();
    // parse the subroutineDec tree
    string data;
    for (auto &p: subroutine_dec_tree) {
        data = p.second.data();
        boost::trim(data);
        if (p.first == "keyword" &&
            (data == "constructor" || data == "function" || data == "method")) {
            // 'constructor'|'function'|'method'
            subroutine_kind = data;
        } else if ((p.first == "keyword" && data == "void") ||
                   (p.first == "keyword" &&
                    (data == "int" || data == "char" || data == "boolean")) ||
                   (p.first == "identifier" &&
                    (data == className || std::find(class_type.begin(), class_type.end(), data) != class_type.end()))) {
            //  ('void' | type)
            subroutine_return_type = data;
        } else if (p.first == "identifier") {
            //  subroutineName
            subroutine_name = className + "." + data;
        } else if (p.first == "parameterList") {
            //  parameterList
            generate_parameter_list(p.second);
        } else if (p.first == "subroutineBody") {
            //  subroutineBody
            generate_subroutine_body(p.second);
        }
    }
}

void CodeGen::generate_parameter_list(const pt &parameter_list_tree) {
    string type;
    string name;
    string kind = "argument";
    int arg_num;
    // push n+1 argument on to the stack if subroutine_kind == method
    if (subroutine_kind == "method") {
        arg_num = 1;
        // define this as the first argument
        st.define("this", className, kind);
    } else // otherwise, push n args(function/constructor)
        arg_num = 0;
    // parse the parameterList tree
    string data;
    for (auto &p: parameter_list_tree) {
        data = p.second.data();
        boost::trim(data);
        // ((type varName) (',' type varName)*)?
        if ((p.first == "keyword" &&
             (data == "int" || data == "char" || data == "boolean")) ||
            (p.first == "identifier" &&
             (data == className || std::find(class_type.begin(), class_type.end(), data) != class_type.end()))) {
            type = data;
        } else if (p.first == "identifier") {
            name = data;
            arg_num += 1;
            st.define(name, type, kind);
        }
    }
}

void CodeGen::generate_subroutine_body(const pt &subroutine_body_tree) {
    local_num = 0;
    pt::const_iterator it = subroutine_body_tree.begin();
    it++; // pass the { symbol
    // varDec
    while (it->first == "varDec") {
        generate_var_dec(it->second);
        it++;
    }
    writer.write_function(subroutine_name, local_num);
    if (subroutine_kind == "constructor") {
        writer.alloc_memory(field_num);
    } else if (subroutine_kind == "method") {
        writer.set_this();
    }
    // statements
    if (it->first == "statements") {
        generate_statements(it->second);
        it++;
    }
    // '}'
    it++;
}

void CodeGen::generate_var_dec(const pt &var_dec_tree) {
    string name;
    string type;
    string kind = "local";
    // parse the varDec tree
    string data;
    for (auto &p: var_dec_tree) {
        data = p.second.data();
        boost::trim(data);
        // 'var'
        // type
        if ((p.first == "keyword" &&
             (data == "int" || data == "char" || data == "boolean")) ||
            (p.first == "identifier" &&
             (data == className || std::find(class_type.begin(), class_type.end(), data) != class_type.end()))) {
            type = data;
        }
            // varName
        else if (p.first == "identifier") {
            name = data;
            st.define(name, type, kind);
            local_num += 1;
        }
        // (',' varName)*
        // ';'
    }
}

void CodeGen::generate_statements(const pt &statements_tree) {
    // parse the statements tree
    for (auto &p: statements_tree) {
        // statement*
        if (p.first == "letStatement") {
            generate_let(p.second);
        } else if (p.first == "ifStatement") {
            generate_if(p.second);
        } else if (p.first == "whileStatement") {
            generate_while(p.second);
        } else if (p.first == "doStatement") {
            generate_do(p.second);
        } else if (p.first == "returnStatement") {
            generate_return(p.second);
        } else {
            cerr << "Invalid statement detected: " << p.first << endl;
            exit(1);
        }
    }
}

void CodeGen::generate_let(const boost::optional<const pt &> &let_tree) {
    /**
     * e.g.
     * let sum = a + b;
     *
     * push [segment] [index]
     * push [segment] [index]
     * Add
     * pop [segment] [index]
     */

    string type = "local";
    // parse the let statement
    // use manually iterator to iterate the content inside <letStatement> .. </letStatement>
    pt::const_iterator it = let_tree->begin();
    // 'let'
    it++;
    // varName -> 3. the destination variable
    string var_name;
    string kind;
    int index;
    if (it->first == "identifier") {
        var_name = it->second.data();
        boost::trim(var_name);
        kind = st.kind_of(var_name);
        index = st.index_of(var_name);
//        type = st.type_of(var_name);
//        if (type == "Array")

    } else {
        cerr << "varName not detected in generate_let(), compilation failed." << endl;
        exit(1);
    }
    it++;
    string data = it->second.data();
    boost::trim(data);
    // ('[' expression ']')? -> 3. array index
    if (it->first == "symbol" && data == "[") {
        // represent that var is an array index
        writer.write_push(kind, index);
        type = "Array";

        it++;
        generate_expression(it->second);
        it++;
        data = it->second.data();
        boost::trim(data);
        if (it->first != "symbol" || data != "]") {
            cerr << "No ] detected in letStatement, mainly in varName[expression] clause, generate_let() failed."
                 << endl;
            exit(1);
        }
        it++;
        writer.write_arithmetic("+");
    }
    data = it->second.data();
    boost::trim(data);
    // '=' -> 2. assignment, use pop
    if (it->first == "symbol" && data == "=") {
        it++;
    } else {
        cerr << "Invalid symbol detected: " << it->second.data() << endl;
        exit(1);
    }

    // expression -> 1. evaluate expression and push onto the stack
    generate_expression(it->second);
    it++;
    // ';'
    data = it->second.data();
    boost::trim(data);
    if (it->first == "symbol" && data == ";") {
        it++;
    } else {
        cerr << "Invalid symbol detected: " << it->second.data() << endl;
        exit(1);

    }
    /**
     * pop pointer 1 // THAT = address of b[j]
        push that 0 // stack top = b[j]
        pop temp 0 // temp 0 = b[j]
        pop pointer 1 // THAT = address of a[i]
        push temp 0 // stack top = b[j]
        pop that 0 // a[i] = b[j]
     */
    if (type != "Array")
        writer.write_pop(kind, index);
    else {
        if (type != "Array") {
            writer.write_pop("pointer", 1);
            writer.write_push("that", 0);
        }
        writer.write_pop("temp", 0);
        writer.write_pop("pointer", 1);
        writer.write_push("temp", 0);
        writer.write_pop("that", 0);
    }
}

void CodeGen::generate_if(const boost::optional<const pt &> &if_tree) {
    int label_count = branch_count;
    branch_count++;
    /**
     * if format:
     *
     * expression1
     * not
     * if-goto false_labelx
     * label true_labelx
     *  true_statements
     * goto end_labelx
     * label false_labelx
     *  false_statements
     * label end_labelx
     */
    // parse the if statement
    pt::const_iterator it = if_tree->begin();
    // 'if'
    string data = it->second.data();
    boost::trim(data);
    if (it->first != "keyword" || data != "if") {
        cerr << "No if keyword detected in if statement, generate_if() failed." << endl;
        exit(1);
    }
    it++;
    data = it->second.data();
    boost::trim(data);
    // '('
    if (it->first != "symbol" || data != "(") {
        cerr << "No ( symbol detected in if statement, generate_if() failed." << endl;
        exit(1);
    }
    it++;
    // expression
    generate_expression(it->second);
//    output << "not" << endl;
    writer.write_arithmetic("~");
    it++;
    // ')'
    data = it->second.data();
    boost::trim(data);
    if (it->first != "symbol" || data != ")") {
        cerr << "No ) symbol detected in if statement, generate_if() failed." << endl;
        exit(1);
    }
    it++;

    // if-goto false_labelx
    // label true_labelx
    writer.write_if("false_label" + std::to_string(label_count));
//    output << "if-goto false_label" << label_count << endl;
    writer.write_label("true_label" + std::to_string(label_count));
//    output << "label true_label" << label_count << endl;

    // '{'
    data = it->second.data();
    boost::trim(data);
    if (it->first != "symbol" || data != "{") {
        cerr << "No { symbol detected in if statement, generate_if() failed." << endl;
        exit(1);
    }
    st.subroutine_new_scope();
    it++;
    // statements
    generate_statements(it->second);
    it++;
    // '}'
    data = it->second.data();
    boost::trim(data);
    if (it->first != "symbol" || data != "}") {
        cerr << "No } symbol detected in if statement, generate_if() failed." << endl;
        exit(1);
    }
    st.close_current_scope();
    it++;

    // goto end_labelx
//    output << "goto end_label" << label_count << endl;
    writer.write_goto("end_label" + std::to_string(label_count));
    // label false_labelx
//        output << "label false_label" << label_count << endl;
    writer.write_label("false_label" + std::to_string(label_count));

    // ('else' '{' statements '}')?
    if (it != if_tree->end()) {
        // else
        data = it->second.data();
        boost::trim(data);
        if (it->first != "keyword" || data != "else") {
            cerr << "No keyword else detected, generate_if() failed." << endl;
            exit(1);
        }
        it++;
        // {
        data = it->second.data();
        boost::trim(data);
        if (it->first != "symbol" || data != "{") {
            cerr << "No { symbol detected in if statement, generate_if() failed." << endl;
            exit(1);
        }
        st.subroutine_new_scope();
        it++;

        // statements
        generate_statements(it->second);
        it++;
        // }
        data = it->second.data();
        boost::trim(data);
        if (it->first != "symbol" || data != "}") {
            cerr << "No } symbol detected in if statement, generate_if() failed." << endl;
            exit(1);
        }
        st.close_current_scope();
        it++;
    }
    // label end_labelx
//    output << "label end_label" << label_count << endl;
    writer.write_label("end_label" + std::to_string(label_count));
}

void CodeGen::generate_while(const boost::optional<const pt &> &while_tree) {
    /**
     * while format:
     *
     * label while_labelx
     *      condition
     *      not
     *      if-goto end_while_labelx
     *      statements
     *      goto while_labelx
     * label end_while_labelx
     */

    int label_count = branch_count;
    branch_count++;

    // parse the while statement
    pt::const_iterator it = while_tree->begin();
    // 'while'
    string data = it->second.data();
    boost::trim(data);
    if (it->first != "keyword" || data != "while") {
        cerr << "No while keyword detected in while statement, generate_while() failed." << endl;
        exit(1);
    }
    it++;

    // label while_labelx
//    output << "label while_label" << label_count << endl;
    writer.write_label("while_label" + std::to_string(label_count));

    // '('
    data = it->second.data();
    boost::trim(data);
    if (it->first != "symbol" || data != "(") {
        cerr << "No ( symbol detected in while statement condition, generate_while() failed." << endl;
        exit(1);
    }
    it++;
    // expression
    generate_expression(it->second);
    it++;

    // not
//    output << "not" << endl;
    writer.write_arithmetic("~");
    // if-goto end_while_labelx
//    output << "if-goto end_while_label" << label_count << endl;
    writer.write_if("end_while_label" + std::to_string(label_count));

    // ')'
    data = it->second.data();
    boost::trim(data);
    if (it->first != "symbol" || data != ")") {
        cerr << "No ) symbol detected in while statement condition, generate_while() failed." << endl;
        exit(1);
    }
    it++;
    // '{'
    data = it->second.data();
    boost::trim(data);
    if (it->first != "symbol" || data != "{") {
        cerr << "No { symbol detected in while statement body, generate_while() failed." << endl;
        exit(1);
    }
    st.subroutine_new_scope();
    it++;
    // statements
    generate_statements(it->second);
    it++;
    // goto while_labelx
//    output << "goto while_label" << label_count;
    writer.write_goto("while_label" + std::to_string(label_count));
    // '}'
    data = it->second.data();
    boost::trim(data);
    if (it->first != "symbol" || data != "}") {
        cerr << "No } symbol detected in while statement body, generate_while() failed." << endl;
        exit(1);
    }
    st.close_current_scope();
    it++;

    // label end_while_labelx
//    output << "label end_while_label" << label_count << endl;
    writer.write_label("end_while_label" + std::to_string(label_count));
}

void CodeGen::generate_do(const boost::optional<const pt &> &do_tree) {
    // parse the do statement
    pt::const_iterator it = do_tree->begin();
    // 'do'
    string data = it->second.data();
    boost::trim(data);
    if (it->first != "keyword" || data != "do") {
        cerr << "No do keyword detected in do Statement, generate_do() failed." << endl;
        exit(1);
    }
    it++;
    // subroutineCall
    generate_subroutine_call(it);
//    it++;
    // ';'
    data = it->second.data();
    boost::trim(data);
    if (it->first != "symbol" || data != ";") {
        cerr << "No ; symbol detected in do Statement, generate_do() failed." << endl;
        exit(1);
    }
    it++;
    // pop temp 0
//    output << "pop temp 0" << endl;
    writer.write_pop("temp", 0);
}

void CodeGen::generate_return(const boost::optional<const pt &> &return_tree) {
    if (subroutine_kind == "constructor") {
        writer.constructor_return();
        return;
    } else if (subroutine_return_type == "void") {
        writer.void_return();
        return;
    }
    // parse the return statement
    pt::const_iterator it = return_tree->begin();
    // 'return'
    string data = it->second.data();
    boost::trim(data);
    if (it->first != "keyword" || data != "return") {
        cerr << "No return keyword detected in return statement, generate_return() failed." << endl;
        exit(1);
    }
    it++;
    // expression?
    generate_expression(it->second);
    it++;
    // ';'
    data = it->second.data();
    boost::trim(data);
    if (it->first != "symbol" || data != ";") {
        cerr << "No symbol ; detected in the end of return statement, generate_return() failed." << endl;
        exit(1);
    }
    it++;
    writer.write_return();
}

void CodeGen::generate_expression(const pt &expression_tree) {
    // parse the expression statement
    pt::const_iterator it = expression_tree.begin();

    // term
    if (it->first == "term") {
        generate_term(it->second);
        it++;
    } else {
        cerr << "Term not detected, generate_expression() failed." << endl;
        exit(1);
    }

    pt::const_iterator end = expression_tree.end();
    string op;
    while (it != end) {
        // (op term)*
        string data = it->second.data();
        boost::trim(data);
        if (check_op(data)) {
            op = data;
        } else if (it->first == "term") {
            generate_term(it->second);
            writer.write_arithmetic(op, "binary");
        }
        it++;
    }
}

void CodeGen::generate_term(const pt &term_tree) {
    /**
     * if term is a constant c:
            output "push c"
        if term is a variable var:
            output "push var"
        if term is "unaryOp term":
            compileTerm(term)
            output "unaryOp"
        if term is "f (exp1, exp2, ...)":
            compileExpression(exp1)
            compileExpression(exp2)
            ...
            compileExpression(expn)
            output "call f n”
        if term is "(exp)":
            compileExpression(exp)
     */
    pt::const_iterator it = term_tree.begin();
    pt::const_iterator end = term_tree.end();
    // parse the term statement
//    while (it != end) {
    string data = it->second.data();
    boost::trim(data);
    // integerConstant | stringConstant | keywordConstant
    if (it->first == "integerConstant" || it->first == "stringConstant" ||
        check_keyword_constant(data)) {
        if (data == "true") {
            writer.write_push("constant", 0);
            writer.write_arithmetic("~");
        } else if (data == "false" || data == "null") {
            writer.write_push("constant", 0);
        } else if (data == "this") {
            writer.write_push("pointer", 0);
        } else if (it->first == "stringConstant") {
            int length = (int) data.length() + 1;
            writer.write_push("constant", length);
            writer.write_call("String.new", 1);
            for (const char &c: data) {
                writer.write_push("constant", c);
                writer.write_call("String.appendChar", 2);
            }
            writer.write_push("constant", 32);
            writer.write_call("String.appendChar", 2);
        } else
            output << "push constant " << data << endl;
        it++;
    }
        // '(' expression ')' |
    else if (data == "(") {
        it++;
        if (it->first == "expression") {
            generate_expression(it->second);
            it++;
        }
        it++;
    }
        // unaryOp term
    else if (check_unary_op(data)) {
        const string &op = data;
        it++;
        if (it->first == "term")
            generate_term(it->second);
        else {
            cerr << "No term found in [unaryOp term] clause, generate_term() failed." << endl;
            exit(1);
        }
        it++;
        writer.write_arithmetic(op, "unary");
    } else if (it->first == "identifier" &&
               std::find(class_type.begin(), class_type.end(), data) == class_type.end()) {
        // varName |
        // varName '[' expression ']' |
        string var_name = data;
        string var_kind = st.kind_of(var_name);
        int var_index = st.index_of(var_name);
        it++;
        writer.write_push(var_kind, var_index);
        if (it == end)
            return;
        data = it->second.data();
        boost::trim(data);
        if (it->first == "symbol" && data == "[") {
            it++;
            if (it->first == "expression") {
                generate_expression(it->second);
                it++;

                writer.write_arithmetic("+");
//                    output << "pop pointer 1" << endl;
                writer.write_pop("pointer", 1);
////                    output << "push that 0" << endl;
                writer.write_push("that", 0);
            } else {
                cerr << "No expression detected in term varName [ expression ], generate_term() failed." << endl;
                exit(1);
            }
            it++;
        }
    } else {
        // subroutineCall |
        generate_subroutine_call(it);
//            it++;
    }
//    }
}

void CodeGen::generate_subroutine_call(pt::const_iterator &it) {
    int num; // subroutine arg num
    if (it->first != "identifier") {
        cerr << "No identifier detected in subroutine Call, generate_subroutine_call() failed." << endl;
        exit(1);
    }
    string data = it->second.data();
    boost::trim(data);
    string name = data; // subroutineName / className / varName
    it++;
    data = it->second.data();
    boost::trim(data);
    if (data == "(") {
        // subroutineName '(' expressionList ')' |
        it++; // pass the ( symbol
        if (it->first != "expressionList") {
            cerr
                    << "No expression list detected in subroutineName '(' expressionList ')' subroutine call, generate_subroutine_call() failed."
                    << endl;
            exit(1);
        }
        num = generate_expression_list(it->second);
        it++; // pass the expressionList
        it++; // pass the ) symbol
        string function_name = className + "." + name;
        writer.write_push("pointer", 0);
        writer.write_call(function_name, num + 1);

    } else if (data == ".") {
        // (className | varName) '.' subroutineName '(' expressionList ')'
        /**
         * if data == varName, then call className.subroutineName(varName,expressionList)
         * otherwise, call className.subroutineName(expressionList)
         */
        bool is_className =
                (className == name) || (std::find(class_type.begin(), class_type.end(), name) != class_type.end());

        it++; // pass the . symbol
        if (it->first != "identifier") {
            cerr
                    << "No identifier subroutineName detected in (className | varName) '.' subroutineName '(' expressionList ')', generate_subroutine_call() failed."
                    << endl;
            exit(1);
        }
        data = it->second.data();
        boost::trim(data);
        string function_name;
        if (is_className)
            function_name = name + "." + data;
        else
            function_name = st.type_of(name) + "." + data;

        int arg;
        if (!is_className) {
            arg = 1;
            // varName: pass arg + 1 arguments in, while the first is varName
            string kind = st.kind_of(name);
            int index = st.index_of(name);
            writer.write_push(kind, index);
        } else {
            arg = 0;
            // className: pass arg arguments in, which are determined by expressionList
        }
        it++; // pass the subroutineName identifier
        data = it->second.data();
        boost::trim(data);
        if (it->first != "symbol" || data != "(") {
            cerr
                    << "No symbol ( detected in varName.subroutineName(expressionList), generate_subroutine_call() failed."
                    << endl;
            exit(1);
        }
        it++; // pass the ( symbol
        arg += generate_expression_list(it->second);
        it++;
        data = it->second.data();
        boost::trim(data);
        if (it->first != "symbol" || data != ")") {
            cerr
                    << "No symbol ) detected in varName.subroutineName(expressionList), generate_subroutine_call() failed."
                    << endl;
            exit(1);
        }
        it++; // pass the ) symbol
        writer.write_call(function_name, arg);
    } else {
        cerr << "No valid identifier ( or . detected, generate_subroutine_call() failed." << endl;
        exit(1);
    }
}

int CodeGen::generate_expression_list(const pt &expression_list_tree) {
    int expression_num = 0;
    // parse the expression list tree
    string data;
    for (auto &p: expression_list_tree) {
        data = p.second.data();
        boost::trim(data);
        // (expression (',' expression)* )?
        if (p.first == "expression") {
            generate_expression(p.second);
            expression_num += 1;
        }
    }
    return expression_num;
}

bool CodeGen::check_op(string &s) {
    // '+'|'-'|'*'|'/'|'&'|'|'|'<'|'>'|'='
    if (std::find(ops.begin(), ops.end(), s) != ops.end()) {
        return true;
    }
    return false;
}

bool CodeGen::check_unary_op(const string &s) {
    // '-'|'~'
    return (s == "-" || s == "~");
}

bool CodeGen::check_keyword_constant(const string &s) {
    // 'true'|'false'|'null'|'this'
    return (s == "true") || (s == "false") || (s == "null") || (s == "this");
}
