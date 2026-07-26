#include "ast/AssignmentExpr.h"
#include "codegen/CodeGenerator.h"
#include<iostream>
using namespace std;
AssignmentExpr::AssignmentExpr(
    const std::string& name,
    std::unique_ptr<Expr> value
)
:Name(name),
Value(std::move(value))
{
}
llvm::Value* AssignmentExpr::codegen(CodeGenerator& CG)
{
    llvm::Value* RHS=Value->codegen(CG);
    std::cout<<"Inside AssignmentExpr::codegen\n";
    if(!RHS)
    {//whether the variable already exist?
        std::cout<<"RHS failed"<<endl;
        return nullptr;
    }
    llvm::AllocaInst*Ptr=CG.getNamedValue(Name);
    //Allocate memory for an int

    Ptr=CG.getBuilder().CreateAlloca(
        llvm::Type::getInt32Ty(CG.getContext()),
        nullptr,
        Name
    );

    std::cout<<"Allocated variable"<<Name<<'\n';
    CG.setNamedValue(Name,Ptr);
    CG.getBuilder().CreateStore(RHS,Ptr);
    return RHS;
}