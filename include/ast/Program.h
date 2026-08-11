#pragma once
#include<memory>
#include "ast/Expr.h"


class Program
{
    public:std::vector<std::unique_ptr<Expr>>Statements;
};