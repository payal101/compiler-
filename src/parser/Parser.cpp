#include "parser/Parser.h"
#include "ast/BinaryExpr.h"
#include "ast/NumberExpr.h"
#include "ast/Expr.h"
#include<string>
#include "ast/VariableExpr.h"
#include "ast/AssignmentExpr.h"
Parser::Parser(const std::vector<Token>& tokens)
:Tokens(tokens),Position(0)
{

}
const Token& Parser::peek()const
{
    return Tokens[Position];
}
const Token& Parser::advance()
{
    return Tokens[Position++];
}
bool Parser::match(TokenType type)
{
    if(peek().Type==type)
    {
        advance();
        return true;
    }
    return false;
}
std::unique_ptr<Expr>Parser::parse()
{
    return parseExpression();
}
//I did not write peek next a token which can "see " but will not consume

const Token& Parser::peekNext()const{
    if (Position+1<Tokens.size())
    {
        return Tokens[Position+1];
    }
    return Tokens.back();
}

std::unique_ptr<Expr>Parser::parsePrimary()
{
    if(peek().Type==TokenType::Number)
    {
        int value=std::stoi(peek().Text);
        advance();
        return std::make_unique<NumberExpr>(value);
    }
     if(peek().Type==TokenType::Identifier)
    {
        std::string name=peek().Text;
        advance();
        return std::make_unique<VariableExpr>(name);
    }
    if(match(TokenType::LParen))
    {
        auto expr=parseExpression();
        if(!match(TokenType::RParen))
        {
            return nullptr;
        }
        return expr;

    }
   
    return nullptr;
}

std::unique_ptr<Expr>Parser::parseFactor()
{
    auto left=parsePrimary();
    while(peek().Type==TokenType::Star||peek().Type==TokenType::Slash)
    {
        char op;
        if(peek().Type==TokenType::Star)
        {
            op='*';
        }
        else
        {
            op='/';
        }
        advance();
       auto right=parsePrimary();
        left=std::make_unique<BinaryExpr>(op,std::move(left),std::move(right));
    }
    return left;
}

std::unique_ptr<Expr>Parser::parseTerm()
{
    auto left=parseFactor();
    while(peek().Type==TokenType::Plus||peek().Type==TokenType::Minus)
{
    char op;
    if(peek().Type==TokenType::Plus)
    {
        op='+';
    }
    else{
        op='-';
    }
    advance();
    auto right=parseFactor();
    left=std::make_unique<BinaryExpr>(op,std::move(left),std::move(right));
}

return left;
}
std::unique_ptr<Expr>Parser::parseExpression()
{
    if(peek().Type==TokenType::Identifier && peekNext().Type==TokenType::Equal)
    {
        std::string name=peek().Text;
        advance();
        match(TokenType::Equal);
        auto rhs=parseExpression();
    return std::make_unique<AssignmentExpr>(
        name,
        std::move(rhs)
    );
  }
    return parseTerm();
}