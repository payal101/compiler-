
#include "ast/Ifstmt.h"
#include "codegen/CodeGenerator.h"
#include <iostream>
Ifstmt::Ifstmt(
    std::unique_ptr<Expr> condition,
    std::unique_ptr<BlockStmt> thenBlock,
std::unique_ptr<BlockStmt>elseBlock)
    : Condition(std::move(condition)),
      ThenBlock(std::move(thenBlock)),
      ElseBlock(std::move(elseBlock))
{
}

Expr* Ifstmt::getCondition() const
{
    return Condition.get();
}

BlockStmt* Ifstmt::getThenBlock() const
{
    return ThenBlock.get();
}
BlockStmt*Ifstmt::getElseBlock() const
{
    return ElseBlock.get();
}
llvm::Value* Ifstmt::codegen(CodeGenerator& CG)
{

    llvm::Value*cond=Condition->codegen(CG);
    if(!cond)
    {
        return nullptr;
    }
    llvm::Function*function=CG.getBuilder().GetInsertBlock()->getParent();
     llvm::Value*last=nullptr;
    llvm::BasicBlock*thenBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "then",
        function
    );
    llvm::BasicBlock*elseBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "else",
        function
    );
    llvm::BasicBlock*mergeBB=llvm::BasicBlock::Create(
        CG.getContext(),
        "ifend",function
    );
    
    CG.getBuilder().CreateCondBr(cond,thenBB,elseBB);
CG.getBuilder().SetInsertPoint(thenBB);
for(auto &stmt:ThenBlock->Statements)
{
    last=stmt->codegen(CG);
}
   if(!CG.getBuilder().GetInsertBlock()->getTerminator())
   {
    CG.getBuilder().CreateBr(mergeBB);
   }
    CG.getBuilder().SetInsertPoint(elseBB);
        if(ElseBlock)
{
    for(auto &stmt:ElseBlock->Statements)
    {
        last=stmt->codegen(CG);
    }
}
if(!CG.getBuilder().GetInsertBlock()->getTerminator())
{
     CG.getBuilder().CreateBr(mergeBB);
   
}

 



CG.getBuilder().SetInsertPoint(mergeBB);

    std::cout<<"Inside IfStmt::codegen\n";
    return last;
}


