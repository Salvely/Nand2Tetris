#include "CodeWriter.hh"
#include "common.h"
#include <sstream>
#include <iostream>

using std::ostringstream;
using std::endl;

CodeWriter::CodeWriter(string output_file) {
    output.open(output_file);
}

void CodeWriter::set_file_name(string filename) {
    this->filename = filename;
    //TODO: left for symbol, such as xxx.symbol
}

void push_value(ostringstream &os) {
    // push the result on to the stack
    os << "@SP" << endl;
    os << "A=M" << endl;
    os << "M=D" << endl;
    os << "@SP" << endl;
    os << "M=M+1" << endl;
}

void pop_value(ostringstream &os) {
    // pop the first value
    os << "@SP" << endl;
    os << "M=M-1" << endl;
    os << "@SP" << endl;
    os << "A=M" << endl;
    os << "D=M" << endl;
}

void write_branch(ostringstream& os, string jump) {
    // TODO: wait until chapter 8 is learned
}
void CodeWriter::write_arithmetic(string command) {
    // TODO: wait until chapter 8 is learned
    /**
     * sp = sp - 1
     * value1 = *sp
     * sp = sp - 1
     * value2 = value1 op *sp
     * *sp = value2
     * sp = sp + 1
     */
    ostringstream os;
    pop_value(os);

    if (command == "neg") {
        os << "D=-D" << endl;
    } else if (command == "not") {
        os << "D=!D" << endl;
    } else if (command == "eq") {}
    else if (command == "gt") {}
    else if (command == "lt") {}
    else {
        // pop the second value
        os << "@SP" << endl;
        os << "M=M-1" << endl;
        os << "@SP" << endl;
        os << "A=M" << endl;
        if (command == "add") { os << "D=D+M" << endl; }
        else if (command == "sub") { os << "D=D-M" << endl; }
        else if (command == "and") { os << "D=D&M" << endl; }
        else if (command == "or") { os << "D=D|M" << endl; }
    }

    push_value(os);
    output << os.str() << std::endl;
}

void CodeWriter::write_push_pop(c_type type, string segment, int index) {
    //TODO: Write_push_pop, wait until chapter 8 is learned ans write_arithmetic is done
    string assembly;
    if (type == C_PUSH) {}
    else if (type == C_POP) {}
    output << assembly << std::endl;
}

void CodeWriter::close() {
    output.close();
}

void CodeWriter::write_init() {

}

void CodeWriter::write_label(string label) {

}

void CodeWriter::write_goto(string label) {

}

void CodeWriter::write_if(string label) {

}

void CodeWriter::write_call(string function_name, int arg_num) {

}

void CodeWriter::write_return() {

}

void CodeWriter::write_function(string function_name, int local_num) {

}
