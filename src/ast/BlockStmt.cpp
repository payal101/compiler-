#include "ast/BlockStmt.h"
#include "codegen/CodeGenerator.h"

llvm::Value*BlockStmt::codegen(CodeGenerator&CG)
{
    llvm::Value*last=nullptr;
    for(auto&stmt:Statements)
    {
        last=stmt->codegen(CG);
    }
    return last;
}