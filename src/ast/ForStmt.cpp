#include "ast/ForStmt.h"
#include <iostream>
#include "codegen/CodeGenerator.h"
#include "ast/BlockStmt.h"
ForStmt::ForStmt(
    std::unique_ptr<Expr>init,
    std::unique_ptr<Expr>condition,
    std::unique_ptr<Expr>increment,
    std::unique_ptr<BlockStmt>body)
    :Init(std::move(init)),
    Condition(std::move(condition)),
    Increment(std::move(increment)),
    Body(std::move(body))
{

}

Expr*ForStmt::getInit()const
{
    return Init.get();
}
Expr*ForStmt::getCondition() const
{
    return Condition.get();
}
Expr*ForStmt::getIncrement()const
{
    return Increment.get();
}
BlockStmt*ForStmt::getBody() const
{
    return Body.get();
}



llvm::Value*ForStmt::codegen(CodeGenerator&CG)
{
    if(Init)
{
    Init->codegen(CG);
}
    llvm::Function*function=
    CG.getBuilder().GetInsertBlock()->getParent();
    llvm::BasicBlock*condBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "for.cond",
        function
    );
    llvm::BasicBlock*bodyBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "for.body",
        function
    );
    llvm::BasicBlock*incBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "for.inc",
        function
    );
    llvm::BasicBlock*endBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "for.end",
        function
    );
    CG.getBuilder().CreateBr(condBB);
    CG.getBuilder().SetInsertPoint(condBB);
    llvm::Value*cond=Condition->codegen(CG);

    CG.getBuilder().CreateCondBr(cond,bodyBB,endBB);
    CG.getBuilder().SetInsertPoint(bodyBB);
CG.pushLoop(endBB,incBB);
   for(auto &stmt : Body->Statements)
   {
    stmt->codegen(CG);
    if(CG.getBuilder().GetInsertBlock()->getTerminator())
    {
        break;
    }
}
CG.popLoop();
if(!CG.getBuilder().GetInsertBlock()->getTerminator())
{
    CG.getBuilder().CreateBr(incBB);
}

CG.getBuilder().SetInsertPoint(incBB);
Increment->codegen(CG);
CG.getBuilder().CreateBr(condBB);
    
    CG.getBuilder().SetInsertPoint(endBB);
    return nullptr;

}