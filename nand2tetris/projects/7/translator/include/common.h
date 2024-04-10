//
// Created by legion on 2024/4/8.
//

#ifndef TRANSLATOR_COMMON_H
#define TRANSLATOR_COMMON_H

#include <vector>
#include <string>

using std::string;

enum c_type {
    C_ARITHMETIC,
    C_PUSH, C_POP,
    C_LABEL,
    C_GOTO, C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
    WHITE_SPACE,
    ILLEGAL
};

std::vector<string> arith_command = {"add", "sub", "neg", "eq", "gt", "lt", "and", "or", "not"};

#endif //TRANSLATOR_COMMON_H
