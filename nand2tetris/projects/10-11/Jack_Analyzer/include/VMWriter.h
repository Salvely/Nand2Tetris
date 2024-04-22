//
// Created by legion on 2024/4/19.
//

#ifndef JACK_ANALYZER_VMWRITER_H
#define JACK_ANALYZER_VMWRITER_H

#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;

// Emits VM commands into a file, using the VM command syntax

class VMWrite {
private:
    ifstream &input;
    ofstream &output;
public:
    /**
     * Creates a new file and prepares it for writing.
     */
    VMWrite(ifstream &ifs, ofstream &ofs);

    /**
     * Writes a VM push command.
     * @param segment CONST, ARG, LOCAL, STATIC, THIS, THAT, POINTER, TEMP
     * @param index
     */
    void write_push(const string& segment, int index);

    /**
     *
     * @param segment CONST, ARG, LOCAL, STATIC, THIS, THAT, POINTER, TEMP
     * @param index
     */
    void write_pop(const string& segment, int index);

    /**
     * write a VM arithmetic command
     * @param command ADD, SUB, NEG, EQ, GT, LT, AND, OR, NOT
     */
    void write_arithemetic(const string& command);

    /**
     * write a VM label command
     * @param label
     */
    void write_label(const string& label);

    /**
     * write a VM goto command
     * @param label
     */
    void write_goto(const string& label);

    /**
     * write a VM if-goto command
     * @param label
     */
    void write_if(const string& label);


    /**
     * write a VM call command
     * @param function_name
     * @param arg_num
     */
    void write_call(const string& function_name, int arg_num);

    /**
     * write a VM function command
     * @param function_name
     * @param local_num
     */
    void write_function(const string& function_name, int local_num);

    /**
     * write a VM return command
     */
    void write_return();

    /**
     * close the output file
     */
    void close();

    void set_this();

    void alloc_memory(int &size);

    void constructor_return();

    void void_return();
};

#endif //JACK_ANALYZER_VMWRITER_H
