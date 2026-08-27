#include "semantic/SymbolTable.h"

bool SymbolTable::declare(const Symbol& symbol)
{
    if (Symbols.find(symbol.getName()) != Symbols.end())
    {
        return false;
    }

    Symbols.emplace(symbol.getName(),symbol);
    return true;
}

Symbol* SymbolTable::lookup(const std::string& name)
{
    auto it = Symbols.find(name);

    if (it == Symbols.end())
    {
        return nullptr;
    }

    return &it->second;
}