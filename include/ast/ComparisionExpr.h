#pragma once

#include "ast/Expr.h"
#include "lexer/Token.h"
#include "codegen/CodeGenerator.h"
#include <memory>

class ComparisionExpr : public Expr
{
private:
    TokenType Op;
    std::unique_ptr<Expr> Left;
    std::unique_ptr<Expr> Right;

public:
    ComparisionExpr(TokenType op,
                   std::unique_ptr<Expr> left,
                   std::unique_ptr<Expr> right);

    llvm::Value* codegen(CodeGenerator& CG) override;
    Expr*getLeft()const{
        return Left.get();
    }
    Expr*getRight()const{
        return Right.get();
    }
    TokenType getOp()const{
        return Op;
    }
};