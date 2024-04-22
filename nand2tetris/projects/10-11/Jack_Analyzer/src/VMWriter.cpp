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
    //TODO: different VM for different command
    if(command == "+") {
        output << "add" << endl;
        return;
    }
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

void VMWrite::set_this() {
    output << "push argument 0" << endl;
    output << "pop pointer 0" << endl;
}

void VMWrite::alloc_memory(int &size) {
    output << "push constant " << size << endl;
    output << "call Memory.alloc 1" << endl;
    output << "pop pointer 0" << endl;
}

void VMWrite::constructor_return() {
    output << "push pointer 0" << endl;
    write_return();
}

void VMWrite::void_return() {
    output << "push constant 0" << endl;
    write_return();
}