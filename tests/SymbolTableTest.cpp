#include "semantic/SymbolTable.h"
#include <string>
#include <cassert>
#include <iostream>

int main()
{
SymbolTable  table;
assert(table.declare(Symbol("x","int",SymbolKind::Variable)));
assert(table.lookup("x")!=nullptr);
assert(table.lookup("x")->getType()=="int");
assert(!table.declare(Symbol("x","int",SymbolKind::Variable)));
assert(table.lookup("y")==nullptr);
std::cout<<"SymbolTable tests passes"<<std::endl;
}
