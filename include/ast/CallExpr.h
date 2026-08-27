#pragma once

#include "Expr.h"
#include <string>
#include <vector>
#include <memory>

class CallExpr : public Expr
{
private:
    std::string Callee;
    std::vector<std::unique_ptr<Expr>> Arguments;

public:
    CallExpr(
        const std::string& callee,
        std::vector<std::unique_ptr<Expr>> arguments
    );

    const std::string& getName() const;

    const std::vector<std::unique_ptr<Expr>>& getArguments() const;

    llvm::Value* codegen(CodeGenerator& CG) override;
};