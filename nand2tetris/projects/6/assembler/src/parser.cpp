#include "parser.hh"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include "symbol_table.hh"

using std::ifstream;
using std::ofstream;
using std::string;

Parser::Parser(string input_file, string output_file)
{
    // open one file for read
    input.open(input_file);
    // open one file for write
    output.open(output_file);
}

int Parser::parse()
{
    int addr_count = 16;

    // first have a whole scan to determine the address of the labels
    int line = 1;
    while (has_more_commands())
    {
        advance();
        c_type type = command_type();
        if (type == WHITE_SPACE)
        {
            continue;
        }
        else if (type == C_Command || type == A_Command)
        {
            line += 1;
        }
        else if (type == L_Command)
        {
            string label_name = label();
            st.add_entry(label_name, line);
        }
        else {
            output << "ILLEGAL Command: " << command << std::endl;
            exit(1);
        }
    }

    // then have a second scan to record the variable and instructions
    input.clear();
    input.seekg(0);

    while (has_more_commands())
    {
        advance();
        c_type type = command_type();
        if (type == WHITE_SPACE)
        {
            continue;
        }
        else if (type == C_Command)
        {
            string dest_field = dest();
            string comp_field = comp();
            string jump_field = jump();
            string dest_bits = cg.dest_bin(dest_field);
            string comp_bits = cg.comp_bin(comp_field);
            string jump_bits = cg.jump_bin(jump_field);
            string command_bin = "111" + comp_bits + dest_bits + jump_bits;
            output << command_bin + '\n';
        }
        else if (type == A_Command)
        {
            string variable = symbol();
            bool decimal = true;
            for (char c : variable)
            {
                if (!isdigit(c))
                {
                    decimal = false;
                    break;
                }
            }
            // judge if @xxx is a decimal number or a variable
            if (decimal)
            {
                string command_bin = "0" + bin(variable);
                output << command_bin + '\n';
            }
            else
            {
                // serach the entry in the symbol_table
                if (st.contains(variable))
                {
                    int address = st.get_address(variable);
                    string command_bin = "0" + bin(std::to_string(address));
                    output << command_bin + '\n';
                }
                else
                {
                    string command_bin = "0" + bin(std::to_string(addr_count));
                    st.add_entry(variable, addr_count);
                    addr_count += 1;
                    output << command_bin + '\n';
                }
            }
        }
    }
    return 0;
}

bool Parser::has_more_commands()
{
    return !input.eof();
}

void Parser::advance()
{
    std::getline(input, command);
    // trim the whitespace around the command
    boost::trim(command);
}

c_type Parser::command_type()
{
    // if it's white space
    if (command == "" || command.find("//") == 0)
    {
        return WHITE_SPACE;
    }
    // if it's c instruction
    else if (command.find('=') != string::npos || command.find(';') != string::npos)
    {
        return C_Command;
    }
    // if it's a instruction
    else if (command.find('@') == 0)
    {
        return A_Command;
    }
    // if it's label
    else if (command.find('(') != string::npos && command.find(")") != string::npos)
    {
        return L_Command;
    }
    return ILLEGAL;
}

string Parser::label()
{
    std::vector<string> vec;
    boost::split(vec, command, boost::is_any_of("()"));
    return vec[1];
}

string Parser::symbol()
{
    // @symbol
    // split the string according to @
    std::vector<string> vec;
    boost::split(vec, command, boost::is_any_of("@"));
    return vec[1];
}

string Parser::dest()
{
    // dest=comp(;jump)
    // split the string according to =
    if (command.find('=') != string::npos)
    {
        std::vector<string> vec;
        boost::split(vec, command, boost::is_any_of("="));
        return vec[0];
    }
    return "";
}

string Parser::comp()
{
    // (dest=)comp(;jump)
    // split the string according to = and ;
    std::vector<string> vec;
    boost::split(vec, command, boost::is_any_of("=;"));
    if (command.find('=') == string::npos)
        return vec[0];
    return vec[1];
}

string Parser::jump()
{
    // (dest=)comp(;jump)
    // split the string according to ;
    std::vector<string> vec;
    if (command.find(';') != string::npos)
    {
        boost::split(vec, command, boost::is_any_of(";"));
        return vec[1];
    }
    return "";
}

string Parser::bin(const string& decimal)
{
    int value = std::stoi(decimal);
    return std::bitset<15>(value).to_string();
}
