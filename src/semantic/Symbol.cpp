
#include "semantic/Symbol.h"
Symbol::Symbol(
const  std::string& name,
const  std::string&  type,
SymbolKind kind
)
:Name(name),
Type(type),
Kind(kind)
{
}
const std::string& Symbol::getName() const
{
return  Name;
}
const std::string&  Symbol::getType() const
{
return Type;
}
SymbolKind Symbol::getKind() const
{
return  Kind;
}
