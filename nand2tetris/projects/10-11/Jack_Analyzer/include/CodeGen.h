//
// Created by legion on 2024/4/20.
//

#ifndef JACK_ANALYZER_CODEGEN_H
#define JACK_ANALYZER_CODEGEN_H

#include "SymbolTable.h"
#include "VMWriter.h"
#include <string>
#include <fstream>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/detail/file_parser_error.hpp>
#include <boost/algorithm/string.hpp>

using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::istringstream;
using pt = boost::property_tree::ptree;
using boost::algorithm::trim;

class CodeGen {
private:
    SymbolTable st;

    string input_filename;
    string output_filename;
    ifstream input;
    ofstream output;

    VMWrite writer;

    string className;

    string subroutine_name;
    string subroutine_kind;
    string subroutine_return_type;

    pt xml_tree;

    int branch_count;

public:
    CodeGen(string input_filename, string output_filename);

    /**
     * 1. create a new class scope
     * 2. setup the class name
     */
    void generate_class();

    /**
     * define the class variable in the class symbol table
     * @param class_var_dec_tree
     */
    void generate_class_var_dec(const pt &class_var_dec_tree);

    /**
     * 1. get function name
     * 2. get subroutine kind(method/function/constructor)
     * 3. get subroutine return type(void/type)
     * 4. call generate_parameter_list()
     * 5. call generate_subroutine_body()
     * @param subroutine_dec_tree
     */
    void generate_subroutine_dec(const pt &subroutine_dec_tree);

    /**
     * 1. define the parameter in symbol table(judge the subroutine_type(function/method/constructor)
     * 2. get parameter num
     * 3. call write_function() in VMWriter
     * @param parameter_list_tree
     */
    void generate_parameter_list(const pt &parameter_list_tree);

    /**
     * 1. create a new subroutine symbol table
     * 2. call var_dec()
     * 3. call statements()
     * @param subroutine_body_tree
     */
    void generate_subroutine_body(const pt &subroutine_body_tree);

    /**
     * 1. define the var type variable in the subroutine symbol table
     * @param var_dec_tree
     */
    void generate_var_dec(const pt &var_dec_tree);

    /**
     * generate statement
     * @param statements_tree
     */
    void generate_statements(const pt &statements_tree);

    /**
     * generate different type of statement according to the statement tag
     * @param statement_tree
     */
    void generate_statement(const pt &statement_tree);

    /**
     * format: let varName ([ expression ])? = expression
     * TODO:
     * 1. generate the expression (after done, the stack top should contains the expression evaluation result)
     * 2. get the varName
     * 3. detect if there is [ symbol in the let statement
     * 4. if there is, then do array indexing, push the stack top value into the array indexed position
     * 5. otherwise, push the stack top value into the varName position
     * TODO VMformat:
     * expression2 evaluation and push the value onto the stack top
     * evaluate the varName | varName [ expression ]
     * pop the stack top value onto the varName | varName [ expression ]
     * @param let_tree
     */
    void generate_let(const boost::optional<const pt &> &let_tree);

    /**
     * format: if ( expression ) { statements } (else { statements })?
     * TODO:
     * 1. generate the expression
     * 2. detect if there is else found
     * 3. if not, jump to the first statements if expression evaluates to true
     * 4. otherwise, besides the above operation, jump to the else statements if expression evaluates to true
     * TODO VMformat:
     * [ evaluate expression ]
     * evaluate the expression value ( 0 or -1)
     * if-goto
     * label true_labelx
     * label false_labelx
     * label end_label
     * @param if_tree
     */
    void generate_if(const boost::optional<const pt &> &if_tree);

    /**
     * format: while ( expression ) { statements }
     * TODO:
     * 1. generate the expression, push the results onto the stack top
     * 2. run statements if expression evaluates to true
     * TODO VMformat:
     * @param while_tree
     */
    void generate_while(const boost::optional<const pt &> &while_tree);

    /**
     * format: do subroutineCall ;
     * TODO:
     * 1. generate subroutineCall vm code
     * TODO VMformat:
     * @param do_tree
     */
    void generate_do(const boost::optional<const pt &> &do_tree);

    /**
     * format: return (expression)? ;
     * TODO:
     * 1. if expression exists, then push the value onto the stack
     * 2. otherwise, return zero
     * TODO Remind:
     * if the expression corresponds to the return type, if there's no return type in the
     * subroutien call, but there is an return expression, report the error
     * TODO VMformat:
     * @param return_tree
     */
    void generate_return(const boost::optional<const pt &> &return_tree);

    /**
     * TODO:
     *
     * TODO VMformat:
     * @param expression_tree
     */
    void generate_expression(const pt &expression_tree);

    /**
     * TODO:
     * TODO VMformat:
     * @param term_tree
     */
    void generate_term(const pt &term_tree);

    /**
     * TODO:
     * TODO VMformat:
     * @param it
     */
    void generate_subroutine_call(pt::const_iterator &it);

    /**
     * @param expression_list_tree
     */
    void generate_expression_list(const pt &expression_list_tree);

    /**
     * TODO:
     * TODO VMformat:
     */
    void generate_op();

    /**
     * TODO:
     * TODO VMformat:
     */
    void generate_unary_op();

    /**
     * TODO:
     * TODO VMformat:
     */
    void generate_keyword_constant();

    /**
     * check if statement exists in the statement_tree head
     * @param statement_tree
     * @param statement
     * @return
     */
    bool check_statement_exists(const pt &statement_tree, const string &statement);

    bool check_op(string &s);

    static bool check_op(const string &s);

    static bool check_unary_op(const string &s);

    static bool check_keyword_constant(const string &s);
};

#endif //JACK_ANALYZER_CODEGEN_H
