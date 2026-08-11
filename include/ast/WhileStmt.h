#pragma once
#include "ast/Expr.h"
#include <memory>
#include "ast/BlockStmt.h"
class  WhileStmt: public Expr{
    public:
    WhileStmt(
        std::unique_ptr<Expr>condition,
        std::unique_ptr<BlockStmt>body
    );
    llvm::Value*codegen(CodeGenerator&)override;
    Expr* getCondition() const;
    BlockStmt* getBody() const;

    private:
    std::unique_ptr<Expr>Condition;
    std::unique_ptr<BlockStmt>Body;
};