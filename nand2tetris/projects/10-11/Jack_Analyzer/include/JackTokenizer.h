//
// Created by legion on 2024/4/16.
//
/**
 * Removes all comments and white space from the input stream and
breaks it into Jack-language tokens, as specified by the Jack grammar
 */
#ifndef JACK_ANALYZER_JACKTOKENIZER_H
#define JACK_ANALYZER_JACKTOKENIZER_H

#include <string>
#include <fstream>
#include <vector>
#include <list>
#include "common.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::list;

class JackTokenizer {
private:
    ifstream input;
    ofstream output;
    string word;
    long val;
    list<string> tokens;
    string input_filename;
    string output_filename;

public:
    /**
     * Opens the input file/stream and gets ready to tokenize it.
     * @param filename the file needs to be tokenized
     */
    JackTokenizer(string input_filename);

    /**
     * Get the output filename from the input fiilname.
     * The output file must resides in the output directory, while the input file is in the test directory.
     * for example:
     * - input filename: ../test/Square/Main.jack
     * - output filename: ../output/Square/MainT.xml
     * @param input_filename filename of the input file
     */
    void get_output_filename(string input_filename);

    /**
     * @return if we have more tokens in the file
     */
    bool has_more_tokens();

    /**
     * Gets the next token from the input and makes it the current token. This
     * method should only be called if hasMoreTokens() is true.
     * Initially there is no current token.
     */
    void advance();

    /**
     * @return the type of the current token
     */
    TOKEN_TYPE token_type();

    /**
     * Returns the keyword which is the current token.
     * Should be called only when tokenType() is KEYWORD.
     * @return the keyword type of the current token
     */
    KEYWORD_TYPE keyword();

    /**
     * @return the character which is the current token.
     * Should be called only when tokenType() is SYMBOL.
     */
    string symbol();

//    /**
//     * Returns the identifier which is the current token.
//     * Should be called only when tokenType() is IDENTIFIER
//     * @return the identifier which is the current token
//     */
//    string identifier();

//    /**
//     * Returns the integer value of the current token.
//     * Should be called only when tokenType() is INT_CONST.
//     * @return the integer value of the current token
//     */
//    int int_val();

    /**
     * Returns the string value of the current token, without the double quotes.
     * Should be called only when tokenType() is STRING_CONST.
     * @return the string value of the current token
     */
    string string_val();

    /**
     * Tokenize the input file and generate the .xml output file
     * @return if compilation success
     */
    int compile();

    /**
     * judge if a token is an illegal identifier
     * @return if a token is an illegal identifier
     */
    bool legal_identifier();
};

#endif //JACK_ANALYZER_JACKTOKENIZER_H
