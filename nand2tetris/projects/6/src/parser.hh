#include <string>
#include <fstream>

using std::istream;
using std::ostream;
using std::string;

enum c_type
{
    A_Command,
    C_Command,
    L_Command
};

// parse the input
class Parser
{
private:
    istream input;
    ostream output;

public:
    /// @brief  Opens the input file/stream and gets ready to parse it.
    /// @param input_file
    Parser(string input_file);

    /// @brief judge if there more commands in the input
    /// @return boolean
    bool has_more_commands();

    /// @brief Reads the next command from the input and makes it the current command.
    /// Should be called only if hasMoreCommands () is true.Initially there is no current command.
    void advance();

    /// @brief return the type of the command
    /// A_Command for @xxx, xxx is a symbol or a decimal number
    /// C_Command for dest=comp;jump
    /// L_Command for (XXX) where xxx is a label
    /// @return c_type enum
    c_type command_type();

    /// @brief Returns the symbol or decimal Xxx of the current command @Xxx or (Xxx).
    /// Should be called only when commandType() is A_COMMAND or L_COMMAND.
    /// @return the symbol or decimal Xxx of the current command @Xxx or (Xxx).
    string symbol();

    /// @brief return the dest field of the command only when commandType() == C_Command
    /// @return the dest field of the command
    string dest();

    /// @brief return the comp field of the command only when commandType() == C_Command
    /// @return the comp field of the command
    string comp();

    /// @brief return the jump field of the command only when commandType() == C_Command
    /// @return the jump field of the command
    string jump();
};