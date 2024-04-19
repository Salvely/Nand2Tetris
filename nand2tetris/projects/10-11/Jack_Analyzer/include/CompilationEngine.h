//
// Created by legion on 2024/4/16.
//

#ifndef JACK_ANALYZER_COMPILATIONENGINE_H
#define JACK_ANALYZER_COMPILATIONENGINE_H

#include <string>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::string;
using std::istringstream;
using std::ostringstream;

class CompilationEngine {
private:
    string input_filename;
    string output_filename;
    ifstream input;
    ofstream output;
    string tag;
    string closingtag;
    string word;
    istringstream is;
    int ret;
    string line;
    long long read_header;
    ostringstream os;

public:
    /**
     * Creates a new compilation engine with the given input and output.
     * The next routine called must be compileClass().
     */
    CompilationEngine(string input_filename, string output_filename);

    /**
     * Compiles a complete class.
     */
    void compile_class();

    /**
     *  Compiles a static declaration or a field declaration.
     * @return if compilation success
     */
    int compile_class_var_dec();

    /**
     * Compiles a complete method, function, or constructor.
     * @return if compilation success
     */
    int compile_subroutine();

    /**
     *  Compiles a (possibly empty) parameter list, not including the enclosing ‘‘()’’.
     * @return if compilation success
     */
    int compile_parameter_list();

    /**
     * Compiles a var declaration.
     * @return if compilation success
     */
    int compile_var_dec();

    /**
     * Compiles a sequence of statements, not including the enclosing ‘‘{}’’.
     * @return if compilation success
     */
    int compile_statements();

    /**
     * Compile a do statement
     * @return if compilation success
     */
    int compile_do();

    /**
     * Compile a let statement
     * @return if compilation success
     */
    int compile_let();

    /**
     * Compile a while statement
     * @return if compilation success
     */
    int compile_while();

    /**
     * Compile a return statement
     * @return if compilation success
     */
    int compile_return();

    /**
     * Compiles an if statement, possibly with a trailing else clause.
     * @return if compilation success
     */
    int compile_if();

    /**
     * Compiles an expression.
     * @return if compliation success
     */
    int compile_expression();

    /**
     * Compiles a term. This routine is faced with a slight difficulty
     * when trying to decide between some of the alternative parsing
     * rules. Specifically, if the current token is an identifier, the routine
     * must distinguish between a variable, an array entry, and a
     * subroutine call. A single lookahead token, which may be one
     * of ‘‘[’’, ‘‘(’’, or ‘‘.’’ suffices to distinguish between the three possibilities.
     * Any other token is not part of this term and should not be advanced over.
     * @return if compilation success
     */
    int compile_term();

    /**
     * Compiles a (possibly empty) comma-separated list of expressions.
     * @return if compilation success
     */
    int compile_expression_list();

    /**
     *
     * @param token_type type of the token, such as identifier, keyword, etc
     * @param token the token needs to be checked
     * @return if token is valid, return 0, otherwise return -1
     */
    int check_token_valid(const string& token_type, const string& token="");

    /**
     * check if valid type declaration
     * @return if type is valid
     */
    int compile_type();

    int compile_subroutine_body();

    void next_line();

    void stringbuf_clear();

    int compile_statement();

    int compile_subroutine_call();

    int compile_unary_op();

    int compile_keyword_constant();

    int compile_op();

    void write_nonterminal(const string& non_terminal);

    void write_close_nonterminal(const string& non_terminal);

    int check_op(const string &token_type);
};

#endif //JACK_ANALYZER_COMPILATIONENGINE_H
