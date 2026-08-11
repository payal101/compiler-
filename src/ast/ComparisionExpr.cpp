#include "ast/ComparisionExpr.h"
#include "codegen/CodeGenerator.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

ComparisionExpr::ComparisionExpr(TokenType op,
std::unique_ptr<Expr>left,
std::unique_ptr<Expr>right)
:Op(op),
Left(std::move(left)),
Right(std::move(right))
{

}
llvm::Value*ComparisionExpr::codegen(CodeGenerator& CG)
{
    llvm::Value* L=Left->codegen(CG);
    llvm::Value*R=Right->codegen(CG);
    switch(Op)
    {
        case TokenType::Less:
        return CG.getBuilder().CreateICmpSLT(L,R,"cmptmp");

         case TokenType::LessEqual:
        return CG.getBuilder().CreateICmpSLE(L,R,"cmptmp");


         case TokenType::GreaterEqual:
        return CG.getBuilder().CreateICmpSGE(L,R,"cmptmp");

         case TokenType::EqualEqual:
        return CG.getBuilder().CreateICmpEQ(L,R,"cmptmp");

         case TokenType::Greater:
        return CG.getBuilder().CreateICmpSGT(L,R,"cmptmp");

         case TokenType::NotEqual:
        return CG.getBuilder().CreateICmpNE(L,R,"cmptmp");
       default:
       return nullptr;
        
    }


}