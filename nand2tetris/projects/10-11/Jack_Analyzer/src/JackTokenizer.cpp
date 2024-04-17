//
// Created by legion on 2024/4/16.
//

#include "JackTokenizer.h"
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

using std::cerr;
using std::endl;
using std::cout;

JackTokenizer::JackTokenizer(string input_filename) {
    this->input_filename = input_filename;
    input.open(input_filename);
    get_output_filename(input_filename);
    boost::filesystem::path p(output_filename);
    if (!exists(p.parent_path()))
        boost::filesystem::create_directories(p.parent_path());
    size_t index = output_filename.find('\\');
    output_filename.replace(index, 1, "/");
    output.open(output_filename, std::fstream::trunc | std::fstream::out);
    if (!output.is_open()) {
        cerr << "Output file " << output_filename << " not opened." << endl;
        exit(1);
    }
}

int JackTokenizer::compile() {
    output << "<tokens>" << endl;
    while (has_more_tokens()) {
        advance();
    }
    for (string &token: tokens) {
        word = token;
        TOKEN_TYPE type = token_type();
        if (type == COMMENT) {
            continue;
        } else if (type == KEYWORD) {
            KEYWORD_TYPE key_type = keyword();
        } else if (type == SYMBOL) {
            word = symbol();
        } else if (type == IDENTIFIER) {
            string iden = word;
        } else if (type == INT_CONST) {
            int value = val;
        } else if (type == STRING_CONST) {
            word = string_val();
        } else {
            cerr << "Illegal token: " << word << " in file " << input_filename << endl;
            exit(1);
        }
        string type_str = get_key(type);
        output << "<" << type_str << ">" << " " << word << " " << "</" << type_str << ">" << endl;
    }
    output << "</tokens>" << endl;
    return 0;
}

bool JackTokenizer::has_more_tokens() {
    return !input.eof();
}

void JackTokenizer::advance() {
    input >> word;
    if(input.fail()) {
        return;
    }
    if (word.find("/*") != string::npos || word.find("/**") != string::npos || word.find("//") != string::npos) {
        string line;
        if (word == "//") {
            std::getline(input, line);
        } else {
            do {
                std::getline(input, line);
            } while (line.find("*/") == string::npos);
        }
        return;
    }
    if (word.find('\n') != string::npos || word.empty()) {
        return;
    }
    if (word.find("\"") != string::npos) {
        if (std::count(word.begin(), word.end(), '\"') == 1) {
            string str;
            do {
                input >> str;
                word += (" " + str);
            } while (str.find('\"') == string::npos);
        }
    }

    if (word.length() == 1 && std::find(symbols.begin(), symbols.end(), word[0]) != symbols.end()) {
        // there is only one symbol in the token
        tokens.push_back(word);
    } else {
        // there may be the combination of symbol and other elements
        // or just the element
        list<string> elems;
        boost::split(elems, word, boost::algorithm::is_any_of(delims));
        if (elems.size() == 1) {
            // if no symbol contains
            tokens.emplace_back(word);
        } else {
            // if symbol contains
            size_t index = 0;
            size_t len = 0;
            int total_len = word.length();
            for (string &elem: elems) {
                if (!elem.empty()) {
                    tokens.emplace_back(elem);
                    len = elem.length();
                } else {
                    len = 0;
                }
                index += len;
                if (index < total_len) {
                    tokens.emplace_back(string(1, word[index]));
                    index += 1;
                }
            }
        }
    }
}

bool JackTokenizer::legal_identifier() {
    if (std::isdigit(word[0])) {
        return false;
    } else {
        return std::all_of(word.begin(), word.end(), [](char c) { return isalnum(c) || c == '_'; });
    }
}

TOKEN_TYPE JackTokenizer::token_type() {
    char *p;
    val = strtol(word.c_str(), &p, 10);
    if (!(*p)) {
        // identify int constants
        return INT_CONST;
    } else if (word.find("/*") != string::npos || word.find("/**") != string::npos || word.find("//") != string::npos ||
               word.find('\n') != string::npos || word.empty()) {
        // identify comments
        return COMMENT;
    } else if (keywords.find(word) != keywords.end()) {
        // identify keywords
        return KEYWORD;
    } else if (std::find(symbols.begin(), symbols.end(), word[0]) != symbols.end()) {
        // identify symbols
        return SYMBOL;
    } else if (legal_identifier()) {
        return IDENTIFIER;
    } else if (word.find("\"") != string::npos && word != "\n") {
        // identify string constants
        return STRING_CONST;
    } else {
        return ILLEGAL_TOKEN;
    }
}

KEYWORD_TYPE JackTokenizer::keyword() {
    return keywords[word];
}

string JackTokenizer::symbol() {
    if (word[0] == '<') {
        return "&lt;";
    } else if (word[0] == '>') {
        return "&gt;";
    } else if (word[0] == '"') {
        return "&quote;";
    } else if (word[0] == '&') {
        return "&amp;";
    }
    return word;
}

//string JackTokenizer::identifier() {
//    return word;
//}

//int JackTokenizer::int_val() {
//    return val;
//}

string JackTokenizer::string_val() {
    return word.substr(1, word.length() - 2);
}

void JackTokenizer::get_output_filename(string input_filename) {
    this->output_filename = input_filename;
    // find the `test` in the output_filename
    std::size_t index = output_filename.find("test");
    if (index == string::npos) {
        cerr << output_filename << "not in test directory?" << endl;
        exit(1);
    }
    // replace `test` directory with `output`
    output_filename.replace(index, 4, "output");
    // find the `jack` extension in the input_filename
    index = output_filename.find(".jack");
    if (index == string::npos) {
        cerr << output_filename << "not a .jack extension file?" << endl;
        exit(1);
    }
    output_filename.replace(index, 5, "T.xml");
}
