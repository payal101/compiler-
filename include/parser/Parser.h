#pragma once
#include<vector>
#include<memory>
#include "lexer/Token.h"
#include "ast/Expr.h"
class Parser{
    public:
    Parser(const std::vector<Token>&token);
    std::unique_ptr<Expr>parse();

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



};