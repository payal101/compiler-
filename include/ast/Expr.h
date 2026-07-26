#pragma once
#include "llvm/IR/Value.h"
class CodeGenerator;
class Expr {
public:
    virtual ~Expr() = default;

    virtual llvm::Value* codegen(CodeGenerator& CG) = 0;
};