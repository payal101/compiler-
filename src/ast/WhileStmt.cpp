#include "ast/WhileStmt.h"
#include <iostream>
#include "codegen/CodeGenerator.h"
WhileStmt::WhileStmt(
    std::unique_ptr<Expr>condition,
    std::unique_ptr<BlockStmt>body)
    :Condition(std::move(condition)),
    Body(std::move(body))
{

}

Expr* WhileStmt::getCondition() const{
    return Condition.get();
}
BlockStmt*WhileStmt::getBody() const{
    return Body.get();
}
llvm::Value*WhileStmt::codegen(CodeGenerator&CG)
{
    llvm::Function*function=
    CG.getBuilder().GetInsertBlock()->getParent();
    llvm::BasicBlock*condBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "while.cond",
        function
    );
    llvm::BasicBlock*bodyBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "while.body",
        function
    );
    llvm::BasicBlock*endBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "while.end",
        function
    );
    CG.getBuilder().CreateBr(condBB);
    CG.getBuilder().SetInsertPoint(condBB);
    llvm::Value*cond=Condition->codegen(CG);

    CG.getBuilder().CreateCondBr(cond,bodyBB,endBB);
CG.pushLoop(endBB,condBB);
    CG.getBuilder().SetInsertPoint(bodyBB);
    for(auto&stmt:Body->Statements)
    {
        stmt->codegen(CG);
    }

    CG.popLoop();
if(!CG.getBuilder().GetInsertBlock()->getTerminator())
{
    CG.getBuilder().CreateBr(condBB);
}
    
    CG.getBuilder().SetInsertPoint(endBB);
    return nullptr;

}