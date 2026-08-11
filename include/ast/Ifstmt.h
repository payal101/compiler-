#pragma once
#include "ast/Expr.h"
#include <memory>
#include "ast/BlockStmt.h"
class Ifstmt:public Expr
{
    public:
    Ifstmt(
        std::unique_ptr<Expr> condition,
        std::unique_ptr<BlockStmt>thenBlock,
        std::unique_ptr<BlockStmt>elseBlock=nullptr
    );
    llvm::Value*codegen(CodeGenerator&)override;

    Expr*getCondition()const;
    BlockStmt*getThenBlock() const;
    BlockStmt*getElseBlock()const;

private:
std::unique_ptr<Expr>Condition;
std::unique_ptr<BlockStmt>ThenBlock;
std::unique_ptr<BlockStmt>ElseBlock;
};