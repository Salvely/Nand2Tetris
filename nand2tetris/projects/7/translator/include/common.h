//
// Created by legion on 2024/4/8.
//

#ifndef TRANSLATOR_COMMON_H
#define TRANSLATOR_COMMON_H

#include <vector>
#include <string>
#include <unordered_map>

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

static std::vector<string> arith_command = {"add", "sub", "neg", "eq", "gt", "lt", "and", "or", "not"};
static std::vector<string> binary_command = {"add", "sub", "and", "or"};
static std::vector<string> uary_command = {"neg", "not"};
static std::vector<string> condition_command = {"eq", "gt", "lt"};
/**
 * argument -> ARG(DONE)
 * local -> LCL(DONE)
 * static -> xxx.j(DONE)
 * constant -> simply push/pop onto/from the stack(DONE)
 * this -> THIS(DONE)
 * that -> THAT(DONE)
 * pointer -> *(3 + i)
 * temp -> *(5 + i)
 */
static std::unordered_map<string, string> segment_symbol = {
        {"argument", "ARG"},
        {"local",    "LCL"},
        {"this",     "THIS"},
        {"that",     "THAT"},
        {"pointer",  "3"},
        {"temp",     "5"},
};
#endif //TRANSLATOR_COMMON_H
