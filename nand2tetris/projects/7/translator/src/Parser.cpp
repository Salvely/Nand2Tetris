#include "Parser.hh"
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>

using std::string;
using std::cerr;
using std::endl;

Parser::Parser(string input_file, string output_file) : cw(output_file) {
    input.open(input_file);

    std::vector<string> vec;
    boost::split(vec, input_file, boost::is_any_of("."));
    string filename = vec[0];
    cw.set_file_name(filename);
}

void Parser::compile() {
    while (has_more_commands()) {
        advance();
        c_type type = command_type();
        if (type == WHITE_SPACE) {
            continue;
        } else if (type == C_ARITHMETIC) {
            cw.write_arithmetic(command);
        } else if (type == C_PUSH || type == C_POP) {
            string segment = arg1();
            if (segment_symbol.find(segment) != segment_symbol.end()) {
                segment = segment_symbol[segment];
            }
            int index = std::stoi(arg2());
            cw.write_push_pop(type, segment, index);
        } else if (type == C_LABEL) {
            // format: label [name]
            string label = arg1();
            cw.write_label(label);
        } else if (type == C_GOTO) {
            // format: goto [label-name]
            string label = arg1();
            cw.write_goto(label);
        } else if (type == C_IF) {
            // format: if-goto [label-name]
            string label = arg1();
            cw.write_if(label);
        } else if (type == C_FUNCTION) {
            // format: function f [local_num]
            string function_name = arg1();
            int label_num = std::stoi(arg2());
            cw.write_function(function_name, label_num);
        } else if (type == C_CALL) {
            // format: call f [arg_num]
            string function_name = arg1();
            int local_num = std::stoi(arg2());
            cw.write_call(function_name, local_num);
        } else if (type == C_RETURN) {
            // format: return
            cw.write_return();
        } else {
            cerr << "Illegal Command: " << command << endl;
            exit(1);
        }
    }
}

void Parser::advance() {
    // read from the input
    std::getline(input, command);
    // trim the command
    boost::trim(command);
    // delete the comment
    std::vector<string> cmd_parts;
    boost::split(cmd_parts, command, boost::is_any_of("//"));
    command = string(cmd_parts[0]);
    boost::trim(command);
}

string Parser::arg1() {
    std::vector<string> vec;
    boost::split(vec, command, boost::is_any_of(" "));
    return vec[1];
}

string Parser::arg2() {
    std::vector<string> vec;
    boost::split(vec, command, boost::is_any_of(" "));
    return vec[2];
}

c_type Parser::command_type() {
    if (command.empty() || command.find("//") == 0) {
        return WHITE_SPACE;
    } else if (command.find("push") != string::npos) {
        return C_PUSH;
    } else if (command.find("pop") != string::npos) {
        return C_POP;
    } else if (std::find(arith_command.begin(), arith_command.end(), command) != arith_command.end()) {
        return C_ARITHMETIC;
    } else if (command.find("label") != string::npos) {
        return C_LABEL;
    } else if (command.find("goto") != string::npos) {
        return C_GOTO;
    } else if (command.find("if-goto") != string::npos) {
        return C_IF;
    } else if (command.find("call") != string::npos) {
        return C_CALL;
    } else if (command.find("function") != string::npos) {
        return C_FUNCTION;
    } else if (command.find("return") != string::npos) {
        return C_RETURN;
    } else {
        return ILLEGAL;
    }
}

bool Parser::has_more_commands() { return !input.eof(); }