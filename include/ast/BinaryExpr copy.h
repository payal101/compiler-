#pragma once
#include <memory>
#include "ast/Expr.h"

class BinaryExpr:public Expr{
    public:
    BinaryExpr(
        char op,
        std::unique_ptr<Expr>left,
        std::unique_ptr<Expr>right
    );


llvm::Value*codegen(CodeGenerator&CG)override;

private:
char Op;
std::unique_ptr<Expr>Left;
std::unique_ptr<Expr>Right;
};

