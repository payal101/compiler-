#include "ast/NumberExpr.h"
#include"codegen/CodeGenerator.h"

#include "llvm/IR/Constants.h"

NumberExpr::NumberExpr(int value)
:Value(value)
{

}
llvm ::Value*NumberExpr::codegen(CodeGenerator&CG)
{
    return llvm::ConstantInt::get(
        llvm::Type::getInt32Ty(CG.getContext()),
        Value
    );
}