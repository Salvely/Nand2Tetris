//
// Created by legion on 2024/4/20.
//

#ifndef JACK_ANALYZER_CODEGEN_H
#define JACK_ANALYZER_CODEGEN_H

#include "SymbolTable.h"
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;

class CodeGen {
private:
    SymbolTable st;
    string input_filename;
    string output_filename;
    ifstream input;
    ofstream output;

public:
    CodeGen(string input_filename, string output_filename);

    void generate_code();

    void generate_class();

    void generate_class_var_dec();

    void generate_type();

    void generate_subroutine_dec();

    void generate_parameter_list();

    void generate_subroutine_body();

    void generate_var_dec();

    void generate_class_name();

    void generate_subroutine_name();

    void generate_var_name();

    void generate_statements();

    void generate_statement();

    void generate_let();

    void generate_if();

    void generate_while();

    void generate_do();

    void generate_return();

    void generate_expression();

    void generate_term();

    void generate_subroutine_call();

    void generate_expression_list();

    void generate_op();

    void generate_unary_op();

    void generate_keyword_constant();
};

#endif //JACK_ANALYZER_CODEGEN_H
