#include "ast/BinaryExpr.h"
#include "codegen/CodeGenerator.h"
#include <iostream>
using namespace std;

using namespace llvm;

BinaryExpr::BinaryExpr(
    char op,
    std::unique_ptr<Expr>left,
    std::unique_ptr<Expr>right
)
:Op(op),
Left(std::move(left)),
Right(std::move(right))
{

}

Value* BinaryExpr::codegen(CodeGenerator&CG)
{

    auto& Builder=CG.getBuilder();
    Value* L =Left->codegen(CG);
    Value* R=Right->codegen(CG);
    if(!L||!R)
    {
        std::cerr<<"BinaryExpr: nullptr operand\n";
        return nullptr;
    }
    switch(Op)
{
    case '+':
    return Builder.CreateAdd(L,R);
case '-':
return Builder.CreateSub(L,R);

case '*':
return Builder.CreateMul(L,R);

case '/':
return Builder.CreateSDiv(L,R);
default:
return nullptr;
}
}