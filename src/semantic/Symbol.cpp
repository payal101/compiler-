#include "semantic/Symbol.h"

Symbol::Symbol(
    const std::string& name,
    Type type,
    SymbolKind kind
)
    : Name(name),
      ValueType(type),
      Kind(kind)
{
}

Symbol::Symbol(
    const std::string& name,
    Type type,
    SymbolKind kind,
    const std::vector<std::string>& parameters
)
    : Name(name),
      ValueType(type),
      Kind(kind),
      Parameters(parameters)
{
}

const std::string& Symbol::getName() const
{
    return Name;
}

Type Symbol::getType() const
{
    return ValueType;
}

SymbolKind Symbol::getKind() const
{
    return Kind;
}

const std::vector<std::string>& Symbol::getParameters() const
{
    return Parameters;
}