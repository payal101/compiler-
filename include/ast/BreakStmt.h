#pragma once
#include "ast/Expr.h"
#include "ast/Expr.h"
#include "codegen/CodeGenerator.h"
class BreakStmt:public Expr{
    public:
    BreakStmt()=default;
    llvm::Value*codegen(CodeGenerator&CG) override;
};