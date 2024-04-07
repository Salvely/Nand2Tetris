#ifndef __SYMBOL_TABLE_HH__
#define __SYMBOL_TABLE_HH__
#include <string>
#include <unordered_map>

using std::string;
// implement the symbol table
class SymbolTable
{
private:
    std::unordered_map<string, int> symbols = {{"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3}, {"THAT", 4}, {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}, {"R4", 4}, {"R5", 5}, {"R6", 6}, {"R7", 7}, {"R8", 8}, {"R9", 9}, {"R10", 10}, {"R11", 11}, {"R12", 12}, {"R13", 13}, {"R14", 14}, {"R15", 15}, {"SCREEN", 16384}, {"KBD", 24576}};

public:
    /// @brief create a new empty symbol table
    SymbolTable();
    /// @brief add the pair(symbol, address) to the table
    /// @param symbol the key of the pair added: the symbol
    /// @param address the value of the pair added: the value
    void add_entry(const string& symbol, int address);
    /// @brief check if the symbol table contains the symbol
    /// @param symbol the symbol to be searched
    /// @return return if the symbol is in the table
    bool contains(const string& symbol);
    /// @brief get the address of the symbol in the symbol table
    /// @param symbol tbe symbol to be searched
    /// @return the address associated with the symbol
    int get_address(const string& symbol);
};

#endif