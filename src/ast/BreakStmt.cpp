#include "ast/BreakStmt.h"
#include "codegen/CodeGenerator.h"

llvm::Value*BreakStmt::codegen(CodeGenerator&CG)
{
    llvm::BasicBlock*breakTarget=CG.getBreakTarget();
    if(!breakTarget)
    {
        return nullptr;
    }
   return CG.getBuilder().CreateBr(CG.getBreakTarget());
}