//
// Created by legion on 2024/4/16.
//

#include "JackTokenizer.h"

JackTokenizer::JackTokenizer(string input_filename) {

}

bool JackTokenizer::has_more_tokens() {
    return false;
}

void JackTokenizer::advance() {

}

TOKEN_TYPE JackTokenizer::token_type() {
    return SYMBOL;
}

KEYWORD_TYPE JackTokenizer::keyword() {
    return DO;
}

char JackTokenizer::symbol() {
    return 0;
}

string JackTokenizer::identifier() {
    return std::__cxx11::string();
}

int JackTokenizer::int_val() {
    return 0;
}

string JackTokenizer::string_val() {
    return std::__cxx11::string();
}
