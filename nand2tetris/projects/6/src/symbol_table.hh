#include <string>
#include <unordered_map>

using std::string;
// implement the symbol table
class SymbolTable
{

public:
    /// @brief create a new empty symbol table
    SymbolTable();
    /// @brief add the pair(symbol, address) to the table
    /// @param symbol the key of the pair added: the symbol
    /// @param address the value of the pair added: the value
    void add_entry(string symbol, int address);
    /// @brief check if the symbol table contains the symbol
    /// @param symbol the symbol to be searched
    /// @return return if the symbol is in the table
    string contains(string symbol);
    /// @brief get the address of the symbol in the symbol table
    /// @param symbol tbe symbol to be searched
    /// @return the address associated with the symbol
    string get_address(string symbol);
};