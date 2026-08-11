#include "ast/ReturnStmt.h"
#include "codegen/CodeGenerator.h"

ReturnStmt::ReturnStmt(std::unique_ptr<Expr>value)
:Value(std::move(value))
{

}

Expr* ReturnStmt::getValue() const
{
    return Value.get();
}
llvm::Value*ReturnStmt::codegen(CodeGenerator&CG)
{
    llvm::Value* value=Value->codegen(CG);
    if(!value)
    {
        return nullptr;
    }
    CG.getBuilder().CreateRet(value);
    return value;
}