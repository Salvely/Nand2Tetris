//
// Created by legion on 2024/4/16.
//

#ifndef JACK_ANALYZER_COMMON_H
#define JACK_ANALYZER_COMMON_H

enum TOKEN_TYPE {
    KEYWORD, SYMBOL,
    IDENTIFIER, INT_CONST,
    STRING_CONST
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
#endif //JACK_ANALYZER_COMMON_H