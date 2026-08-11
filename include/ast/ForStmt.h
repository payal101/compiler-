#pragma once
#include <memory>
#include "ast/Expr.h"
#include "ast/BlockStmt.h"
#include "codegen/CodeGenerator.h"

class ForStmt:public Expr{
    private:
    std::unique_ptr<Expr> Init;
    std::unique_ptr<Expr> Condition;
    std::unique_ptr<Expr> Increment;
    std::unique_ptr<BlockStmt> Body;
public:
ForStmt(
    std::unique_ptr<Expr>init,
    std::unique_ptr<Expr>condition,
    std::unique_ptr<Expr>increment,
    std::unique_ptr<BlockStmt>body
);
Expr*getInit()const;
Expr*getCondition()const;
Expr*getIncrement()const;
BlockStmt*getBody() const;
llvm::Value* codegen(CodeGenerator&CG)override;
};
