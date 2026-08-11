#pragma once
#include "ast/Expr.h"
#include <memory>
class ReturnStmt:public Expr{
    private:
    std::unique_ptr<Expr>Value;
public:
ReturnStmt(std::unique_ptr<Expr>value);
Expr* getValue()  const;
llvm::Value* codegen(CodeGenerator&CG)override;
};