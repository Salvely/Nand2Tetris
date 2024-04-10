#include <string>
#include <fstream>
#include <vector>
#include "CodeWriter.hh"
#include "common.h"

using std::string;
using std::ifstream;
using std::ofstream;

class Parser {
private:
    ifstream input;
    string command;
    CodeWriter cw;

public:
    /**
     * Opens the input file/stream and gets ready to parse it.
     * @param input_file
     */
    explicit Parser(string input_file, string output_file);

    /**
     * reads in the program, and execute the compile process
     * @return if compile success
     */
    void compile();

    /**
     * judge if there are more commands in the file
     * @return
     */
    bool has_more_commands();

    /**
     * Reads the next command from the input and makes it the current command.
    Should be called only if hasMoreCommands() is true. Initially there is no current command.
     */
    void advance();

    /**
     * Returns the type of the current VM command.
     * C_ARITHMETIC is returned for all the arithmetic commands
     * @return c_type
     */
    c_type command_type();

    /**
     * Returns the first argument of the current command. In the case of C_ARITHMETIC,
    the command itself (add, sub, etc.) is returned.
    Should not be called if the current command is C_RETURN
     * @return the first argument of the current command
     */
    string arg1();

    /**
     * Returns the second argument of the current command.
     * Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL.
     * @return the second argument of the current command
     */
    string arg2();
};