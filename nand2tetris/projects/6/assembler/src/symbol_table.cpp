#include "symbol_table.hh"

SymbolTable::SymbolTable()
= default;

void SymbolTable::add_entry(const string& symbol, int address)
{
    symbols.insert(std::make_pair(symbol, address));
}

bool SymbolTable::contains(const string& symbol)
{
    return symbols.find(symbol) != symbols.end();
}

int SymbolTable::get_address(const string& symbol)
{
    return symbols[symbol];
}
