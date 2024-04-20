//
// Created by legion on 2024/4/19.
//

#ifndef JACK_ANALYZER_VMWRITER_H
#define JACK_ANALYZER_VMWRITER_H

#include <string>

using std::string;

// Emits VM commands into a file, using the VM command syntax

class VMWrite {
public:
    /**
     * Creates a new file and prepares it for writing.
     */
    VMWrite(string input_filename, string output_filename);

    /**
     * Writes a VM push command.
     * @param segment CONST, ARG, LOCAL, STATIC, THIS, THAT, POINTER, TEMP
     * @param index
     */
    void write_push(string segment, int index);

    /**
     *
     * @param segment CONST, ARG, LOCAL, STATIC, THIS, THAT, POINTER, TEMP
     * @param index
     */
    void write_pop(string segment, int index);

    /**
     * write a VM arithmetic command
     * @param command ADD, SUB, NEG, EQ, GT, LT, AND, OR, NOT
     */
    void write_arithemetic(string command);

    /**
     * write a VM label command
     * @param label
     */
    void write_label(string label);

    /**
     * write a VM goto command
     * @param label
     */
    void write_goto(string label);

    /**
     * write a VM if-goto command
     * @param label
     */
    void write_if(string label);


    /**
     * write a VM call command
     * @param function_name
     * @param arg_num
     */
    void write_call(string function_name, int arg_num);

    /**
     * write a VM function command
     * @param function_name
     * @param local_num
     */
    void write_function(string function_name, int local_num);

    /**
     * write a VM return command
     */
    void write_return();

    /**
     * close the output file
     */
    void close();
};

#endif //JACK_ANALYZER_VMWRITER_H
