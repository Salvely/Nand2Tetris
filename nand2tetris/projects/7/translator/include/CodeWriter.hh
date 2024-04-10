#include <string>
#include <fstream>
#include "common.h"

using std::string;
using std::ofstream;

class CodeWriter {
private:
    ofstream output;
    string filename;
public:
    /**
     * Opens the output file/ stream and gets ready to write into it
     * @param output_file
     */
    CodeWriter(string output_file);

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
};
