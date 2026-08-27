#pragma once

#include "semantic/Symbol.h"
#include <string>
#include <unordered_map>

class SymbolTable
{
private:
    std::unordered_map<std::string, Symbol> Symbols;

public:
    bool declare(const Symbol& symbol);
    Symbol* lookup(const std::string& name);
};