//
// Created by legion on 2024/4/19.
//

#include "VMWriter.h"
#include <iostream>

using std::endl;

VMWrite::VMWrite(ifstream &ifs, ofstream &ofs) : input(ifs), output(ofs) {}

void VMWrite::write_push(const string &segment, int index) {
    output << "push " << segment << " " << index << endl;
}

void VMWrite::write_pop(const string &segment, int index) {
    output << "pop " << segment << " " << index << endl;
}

void VMWrite::write_arithemetic(const string &command) {
    output << command << endl;
}

void VMWrite::write_label(const string &label) {
    output << "label " << label << endl;
}

void VMWrite::write_goto(const string &label) {
    output << "goto " << label << endl;
}

void VMWrite::write_if(const string &label) {
    output << "if-goto " << label << endl;
}

void VMWrite::write_call(const string &function_name, int arg_num) {
    output << "call " << function_name << " " << arg_num << endl;
}

void VMWrite::write_function(const string &function_name, int local_num) {
    output << "function " << function_name << " " << local_num << endl;
}

void VMWrite::write_return() {
    output << "return" << endl;
}

void VMWrite::close() {
    output.close();
    input.close();
}