#pragma once
#include <vector>
#include<memory>
#include "ast/Expr.h"


class BlockStmt:public Expr
{
    public:
    std::vector<std::unique_ptr<Expr>>Statements;
    llvm::Value*codegen(CodeGenerator&) override;
};