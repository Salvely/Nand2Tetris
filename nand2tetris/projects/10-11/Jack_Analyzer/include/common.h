//
// Created by legion on 2024/4/16.
//

#ifndef JACK_ANALYZER_COMMON_H
#define JACK_ANALYZER_COMMON_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using std::string;
using std::cerr;
using std::endl;

enum TOKEN_TYPE {
    KEYWORD, SYMBOL,
    IDENTIFIER, INT_CONST,
    STRING_CONST, COMMENT,
    ILLEGAL_TOKEN
};

enum KEYWORD_TYPE {
    CLASS, METHOD, FUNCTION,
    CONSTRUCTOR, INT,
    BOOLEAN, CHAR, VOID,
    VAR, STATIC, FIELD, LET,
    DO, IF, ELSE, WHILE,
    RETURN, TRUE, FALSE,
    NULL_KEY, THIS,
};

static std::unordered_map<string, KEYWORD_TYPE> keywords = {{"class",       CLASS},
                                                            {"constructor", CONSTRUCTOR},
                                                            {"function",    FUNCTION},
                                                            {"method",      METHOD},
                                                            {"field",       FIELD},
                                                            {"static",      STATIC},
                                                            {"var",         VAR},
                                                            {"int",         INT},
                                                            {"char",        CHAR},
                                                            {"boolean",     BOOLEAN},
                                                            {"void",        VOID},
                                                            {"true",        TRUE},
                                                            {"false",       FALSE},
                                                            {"null",        NULL_KEY},
                                                            {"this",        THIS},
                                                            {"let",         LET},
                                                            {"do",          DO},
                                                            {"if",          IF},
                                                            {"else",        ELSE},
                                                            {"while",       WHILE},
                                                            {"return",      RETURN}};
static std::vector<char> symbols = {'{', '}', '(', ')', '[', ']', '.', ',', ';', '+', '-', '*', '/', '&', '|', '<',
                                    '>', '=', '~'};

static string delims = string(symbols.begin(), symbols.end());

string get_key(TOKEN_TYPE type);

static int indent = 0;

#endif //JACK_ANALYZER_COMMON_H
