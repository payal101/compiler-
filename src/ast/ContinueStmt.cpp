#include "ast/ContinueStmt.h"
#include "codegen/CodeGenerator.h"
llvm::Value*ContinueStmt::codegen(CodeGenerator&CG)
{
    llvm::BasicBlock*continueTarget=CG.getContinueTarget();
    if(!continueTarget)
    {
        return nullptr;
    }
   
   return CG.getBuilder().CreateBr(CG.getContinueTarget());
}