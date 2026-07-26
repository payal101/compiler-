#pragma once
#include "ast/Expr.h"
class NumberExpr:public Expr{
    public:
    NumberExpr(int value);
llvm::Value*codegen(CodeGenerator& CG)override;
private:
int Value;
};