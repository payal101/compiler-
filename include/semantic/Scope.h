#pragma once

#include "semantic/SymbolTable.h"
class Scope
{
    private:
    SymbolTable Symbols;
    Scope* Parent;
public:
Scope(Scope*parent=nullptr);
bool declare(const Symbol&symbol);
Scope*getParent();
Symbol* lookup(const std::string& name);
};