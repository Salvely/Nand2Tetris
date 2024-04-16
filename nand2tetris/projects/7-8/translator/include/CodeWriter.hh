#ifndef __CODEWRITER_H__
#define __CODEWRITER_H__

#include <string>
#include <fstream>
#include "common.h"

using std::string;
using std::ofstream;

class CodeWriter {
private:
    ofstream output;
    string filename;
//    int ret_count;
//    int if_count;
    string function_name;

public:
    /**
     * Opens the output file/ stream and gets ready to write into it
     * @param output_file
     */
    CodeWriter(string output_file);

    /**
     * CodeWriter Destructor
     */
    ~CodeWriter();

    /**
     * Informs the code writer that the translation of a new VM file is started.
     * @param filename
     */
    void set_file_name(string filename);

    /**
     * Writes the assembly code that is the translation of the given arithmetic command.
     * @param command
     */
    void write_arithmetic(string command);

    /**
     * Writes the assembly code that is the translation of
     * the given command, where command is either C_PUSH or C_POP
     * @param command
     * @param segment
     * @param index
     */
    void write_push_pop(c_type type, string segment, int index);

    /**
     * close the output file
     */
    void close();

    /**
     * Writes assembly code that effects the VM initialization, also called
        bootstrap code. This code must be placed at the beginning of the output file.
     */
    void write_init();

    /**
     * Writes assembly code that effects the label command.
     * @param label
     */
    void write_label(string label);

    /**
     * Writes assembly code that effects the goto command
     * @param label
     */
    void write_goto(string label);

    /**
     * Writes assembly code that effects the if-goto command.
     * @param label
     */
    void write_if(string label);

    /**
     * Writes assembly code that effects the call command
     * @param function_name
     * @param arg_num
     */
    void write_call(string function_name, int arg_num);

    /**
     * Writes assembly code that effects the return command.
     */
    void write_return();

    /**
     * Writes assembly code that effects the function command.
     * @param function_name
     * @param local_num
     */
    void write_function(string function_name, int local_num);

    /**
     * decrease the SP pointer by 1
     */
    void SP_decrease();

    /**
     * increase the SP pointer by 1
     */
    void SP_increase();

    /**
     * dereference a pointer or assign a value to the pointer
     * where pointer = (segment + index)
     * write from D reg or write to D reg
     */
    void ref_deref_pt(bool deref = true, const string &segment = "SP", int index = 0);

    /**
     * assign the value of D register to a pointer(segment)
     * @param pointer the pointer to be reassigned
     * @param offset the offset to the pointer(segment)
     */
    void reassign_pt(const string &pointer = "SP", int offset = 0);

    /**
     * get the value of a pointer , write to D register
     * @param pointer the pointer which we want to obtain its value
     * @param offset the offset to the pointer(segment)
     */
    void obtain_pt(const string &pointer = "SP", int offset = 0);

    /**
     * push the value into address segment + index
     * @param segment segment we want to push into
     * @param index offset from the base address of the segment
     */
    void basic_push(string segment = "SP", int index = 0);

    /**
     * pop from address segment + index
     * @param segment segment we want to pop from
     * @param index offset from the base address of the segment
     */
    void basic_pop(string segment = "SP", int index = 0);

    /**
     * set register D as -1 or 0 according to the condition
     * @param condition the condition to be judged, such as jt lt eq
     */
    void write_branch(string condition);
};

#endif