#include "semantic/SymbolTable.h"
#include <cassert>
#include <iostream>

int main()
{
    SymbolTable table;

    // Variable
    assert(table.declare(
        Symbol("x", Type::Int, SymbolKind::Variable)
    ));

    // Function with two parameters
    std::vector<std::string> params = {"a", "b"};

    assert(table.declare(
        Symbol(
            "add",
            Type::Int,
            SymbolKind::Function,
            params
        )
    ));

    Symbol* add = table.lookup("add");

    assert(add != nullptr);
    assert(add->getKind() == SymbolKind::Function);

    assert(add->getParameters().size() == 2);
    assert(add->getParameters()[0] == "a");
    assert(add->getParameters()[1] == "b");

    std::cout << "SymbolTable tests passed!\n";
}