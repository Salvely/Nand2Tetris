#include "parser.hh"

Parser::Parser(string input_file)
{
}

bool Parser::has_more_commands()
{
    return false;
}

void Parser::advance()
{
}

c_type Parser::command_type()
{
    return c_type();
}

string Parser::symbol()
{
    return string();
}

string Parser::dest()
{
    return string();
}

string Parser::comp()
{
    return string();
}

string Parser::jump()
{
    return string();
}
