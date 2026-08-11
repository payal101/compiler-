#pragma once
#include <string>
enum class SymbolKind{
    Variable,
    Parameter,
    Function
};

class Symbol{
    private:
    std::string Name;
    std::string Type;
    SymbolKind Kind;
public:
Symbol(
    const std::string& name,
    const std::string& type,
    SymbolKind kind
);
const std::string& getName() const;
const std::string& getType() const;
SymbolKind getKind() const;
};