#pragma once
#include <string>
#include <vector>
#include "semantic/Type.h"

enum class SymbolKind{
    Variable,
    Parameter,
    Function
};

class Symbol{
    private:
    std::string Name;
    Type ValueType;
    SymbolKind Kind;
    std::vector<std::string>Parameters;
public:
Symbol(
    const std::string& name,
    Type type,
    SymbolKind kind
);
Symbol(
    const std::string& name,
    Type type,
    SymbolKind kind,
    const std::vector<std::string>& parameters
);
const std::string& getName() const;
Type getType() const;
SymbolKind getKind() const;
const std::vector<std::string>& getParameters() const;
};