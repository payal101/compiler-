#pragma once
#include "ast/Expr.h"
class ContinueStmt:public Expr
{
    public:
    ContinueStmt()=default;
    llvm::Value*codegen(CodeGenerator&CG)override;
};