#pragma once
#include<vector>
#include<memory>
#include "lexer/Token.h"
#include "ast/Expr.h"
#include "ast/Program.h"
#include "ast/ComparisionExpr.h"
#include "ast/BlockStmt.h"
#include "ast/Ifstmt.h"
#include  "ast/FunctionDec1.h"
class Parser{
    public:
    Parser(const std::vector<Token>&token);
    std::unique_ptr<Program>parse();

    private:
    std::vector<Token>Tokens;
    size_t Position;
    const Token& peek() const;
    const Token& advance();
    const Token& peekNext() const;
    bool match(TokenType type);
    std::unique_ptr<Expr>parseExpression();
    std::unique_ptr<Expr>parseTerm();
    std::unique_ptr<Expr>parseFactor();
    std::unique_ptr<Expr>parsePrimary();
    std::unique_ptr<Expr>parsecomparision();
    std::unique_ptr<BlockStmt>parseBlock();
    std::unique_ptr<Expr>parseStatement();
    std::unique_ptr<Expr>parseIf();
    std::unique_ptr<Expr>parseWhile();
    std::unique_ptr<Expr>parseBreak();
    std::unique_ptr<Expr>parseContinue();
    std::unique_ptr<Expr>parseFor();
    std::unique_ptr<Expr>parseReturn();
    std::unique_ptr<Expr>parseFunction();


};