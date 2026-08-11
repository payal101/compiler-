#pragma once
#include "ast/Expr.h"
#include "ast/BlockStmt.h"
#include <memory>
#include <vector>
#include <string>

class FunctionDec1 :public Expr
{
    private:
    std::string Name;
    std::vector<std::string>  Parameters;
    std::unique_ptr<BlockStmt> Body;

public:
FunctionDec1(
    const std::string& name,
    std::vector<std::string>parameters,
    std::unique_ptr<BlockStmt>body
);
const std::string& getName() const;
const std::vector<std::string>& getParameters() const;
BlockStmt*getBody() const;
llvm::Value*codegen(CodeGenerator&CG)override;
};