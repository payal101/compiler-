#pragma once
#include<memory>
#include<string>

#include"ast/Expr.h"

class AssignmentExpr:public Expr
{
    public:
    AssignmentExpr(
        const std::string& name,
        std::unique_ptr<Expr>value
    );
    llvm::Value* codegen(CodeGenerator& CG)override;
    const std::string& getName()const
    {
        return Name;
    }
    Expr*getValue()const
    {
        return Value.get();
    }
    private:
    std::string Name;
    std::unique_ptr<Expr> Value;
};