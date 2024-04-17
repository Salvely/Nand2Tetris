//
// Created by legion on 2024/4/17.
//
#include "common.h"

string get_key(TOKEN_TYPE type) {
    if (type == KEYWORD) {
        return "keyword";
    } else if (type == SYMBOL) {
        return "symbol";
    } else if (type == IDENTIFIER) {
        return "identifier";
    } else if (type == INT_CONST) {
        return "integerConstant";
    } else if (type == STRING_CONST) {
        return "stringConstant";
    } else {
        cerr << "Token type invalid" << endl;
        exit(1);
    }
}