#include "semantic/Scope.h"
Scope::Scope(Scope* parent)
:Parent(parent)
{
//still dont get the empty parantheses
}
bool Scope::declare(const Symbol&symbol)
{
    return Symbols.declare(symbol);
}
Symbol*Scope::lookup(const std::string& name)
{
    Symbol* symbol=Symbols.lookup(name);
    if(symbol)
    {
        return symbol;
    }
    if(Parent)
    {
        return Parent->lookup(name);
    }
    return nullptr;
}
Scope*Scope::getParent()
{
    return Parent;
}

