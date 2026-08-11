#include "parser/Parser.h"
#include "ast/BinaryExpr.h"
#include "ast/NumberExpr.h"
#include "ast/Expr.h"
#include<string>
#include "ast/VariableExpr.h"
#include "ast/AssignmentExpr.h"
#include "ast/Program.h"
#include "ast/ComparisionExpr.h"
#include "ast/Ifstmt.h"
#include "ast/WhileStmt.h"
#include "ast/BreakStmt.h"
#include "ast/ContinueStmt.h"
#include "ast/ForStmt.h"
#include "ast/ReturnStmt.h"
#include "ast/FunctionDec1.h"
#include "ast/CallExpr.h"

#include <iostream>
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
std::unique_ptr<Program>Parser::parse()
{

    auto program =std::make_unique<Program>();
    while(peek().Type!=TokenType::End)
    {
        auto statement=parseStatement();
        if(!statement)
        {
            return nullptr;
        }
        program->Statements.push_back(std::move(statement));
        if(peek().Type==TokenType::SemiColon)
        {
            advance();
        }
     
    }
    return program;
}
//I did not write peek next a token which can "see " but will not consume

const Token& Parser::peekNext()const{
    if (Position+1<Tokens.size())
    {
        return Tokens[Position+1];
    }
    return Tokens.back();
}
std::unique_ptr<Expr>Parser::parseIf()
{
    std::unique_ptr<BlockStmt> elseBlock=nullptr;
   advance();
   if(!match(TokenType::LParen))
   {
    return nullptr;
   }
   auto condition=parseExpression();
   if(!condition)
   {
    return nullptr;
   }
   if(!match(TokenType::RParen))
   {
    return nullptr;
   }
   auto thenBlock=parseBlock();
   if(!thenBlock)
   {
    return nullptr;
   }
   if(match(TokenType::Else))
   {
    elseBlock=parseBlock();
   }
 return std::make_unique<Ifstmt>(
    std::move(condition),
    std::move(thenBlock),
    std::move(elseBlock)
 );
}
std::unique_ptr<Expr>Parser::parseStatement()
{
    if(peek().Type==TokenType::Function)
    {
        return parseFunction();
    }
    if(peek().Type==TokenType::If)
    {
        return parseIf();
    }
     if(peek().Type==TokenType::While)
      {
        return parseWhile();
      }
    if(peek().Type==TokenType::LBrace)
    {
        return parseBlock();
    }
    if(peek().Type==TokenType::Break)
    {
        return parseBreak();
    }
    if(peek().Type==TokenType::Continue)
    {
        return parseContinue();
    }
    if(peek().Type==TokenType::For)
    {
        return parseFor();
    }
    if(peek().Type==TokenType::Return)
{
    return parseReturn();
} 
    return parseExpression();
    
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
        if(match(TokenType::LParen))
        {
            std::vector<std::unique_ptr<Expr>>arguments;
            if(peek().Type!=TokenType::RParen)
            {
                while(true)
                {
                    auto argument=parseExpression();

                    if(!argument)
                    {
                        return nullptr;
                    }
                    arguments.push_back(std::move(argument));

                    if(!match(TokenType::Comma))
                    {
                        break;
                    }
                }
            }
            if(!match(TokenType::RParen))
            {
                return nullptr;
            }
            return std::make_unique<CallExpr>(
                name,
                std::move(arguments)
            );
        }
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
        auto rhs=parsecomparision();
    return std::make_unique<AssignmentExpr>(
        name,
        std::move(rhs)
    );
  }

    return parsecomparision();
}

std::unique_ptr<Expr>Parser::parsecomparision()
{
    auto  left=parseTerm();
    if(peek().Type == TokenType::Less ||
peek().Type == TokenType::Greater ||
peek().Type == TokenType::EqualEqual ||
peek().Type == TokenType::GreaterEqual ||
peek().Type == TokenType::LessEqual ||
peek().Type == TokenType::NotEqual)
    {
        TokenType op=peek().Type;
        advance();
        auto rhs=parseTerm();
        return std::make_unique<ComparisionExpr>(
            op,
            std::move(left),
            std::move(rhs)
        );
    }
    return left;
}
std::unique_ptr<BlockStmt>Parser::parseBlock()
{
   if(!match(TokenType::LBrace))
   {
    return nullptr;
   }
   auto block=std::make_unique<BlockStmt>();
   while(peek().Type!=TokenType::RBrace&&peek().Type!=TokenType::End)
   {
    auto stmt=parseStatement();
    if(!stmt)
    {
        return nullptr;
    }
    block->Statements.push_back(std::move(stmt));
    if(peek().Type==TokenType::SemiColon)
    {
        advance();
    }
   
   }
    if(!match(TokenType::RBrace))
    {
        return nullptr;
    }
   return block;
}
std::unique_ptr<Expr>Parser::parseWhile()
{
   advance();
   if(!match(TokenType::LParen))
   {
    return nullptr;
   }
   auto condition=parseExpression();
   if(!condition)
   {
    return nullptr;
   }
   if(!match(TokenType::RParen))

   {
    return nullptr;
   }
   auto body=parseBlock();
   if(!body)
   {
    return nullptr;
   }
   return std::make_unique<WhileStmt>(
    std::move(condition),
    std::move(body)
   );
}

std::unique_ptr<Expr>Parser::parseBreak()
{
    advance();
    return std::make_unique<BreakStmt>();

}
std::unique_ptr<Expr>Parser::parseContinue()
{
    advance();
    return std::make_unique<ContinueStmt>();
}
std::unique_ptr<Expr>Parser::parseFor()
{
    advance();
    match(TokenType::LParen);
    auto init=parseExpression();
    match(TokenType::SemiColon);
    auto condition=parseExpression();
    match(TokenType::SemiColon);
    auto increment=parseExpression();
    match(TokenType::RParen);
    auto body=parseBlock();

    return std::make_unique<ForStmt>(
        std::move(init),
        std::move(condition),
        std::move(increment),
        std::move(body)
    );
}

std::unique_ptr<Expr>Parser::parseReturn()
{
    advance();
    auto value=parseExpression();
   if(!value)
   {
    return nullptr;
   }
    return std::make_unique<ReturnStmt>(std::move(value));
}
std::unique_ptr<Expr> Parser::parseFunction()
{
    std::cout << "1: entering parseFunction\n";

    advance(); // function

    std::cout << "2: function consumed, current = "
              << peek().Text << "\n";

    if(peek().Type != TokenType::Identifier)
    {
        std::cout << "ERROR: expected function name\n";
        return nullptr;
    }

    std::string name = peek().Text;
    advance();

    std::cout << "3: name = " << name << "\n";

    if(!match(TokenType::LParen))
    {
        std::cout << "ERROR: expected (\n";
        return nullptr;
    }

    std::cout << "4: ( consumed\n";

    std::vector<std::string> parameters;

    if(peek().Type != TokenType::RParen)
    {
        while(true)
        {
            if(peek().Type != TokenType::Identifier)
            {
                std::cout << "ERROR: expected parameter\n";
                return nullptr;
            }

            parameters.push_back(peek().Text);
            advance();

            if(!match(TokenType::Comma))
            {
                break;
            }
        }
    }

    std::cout << "5: parameters parsed\n";

    if(!match(TokenType::RParen))
    {
        std::cout << "ERROR: expected )\n";
        return nullptr;
    }

    std::cout << "6: ) consumed\n";

    auto body = parseBlock();

    if(!body)
    {
        std::cout << "ERROR: parseBlock failed\n";
        return nullptr;
    }

    std::cout << "7: body parsed\n";

    return std::make_unique<FunctionDec1>(
        name,
        std::move(parameters),
        std::move(body)
    );
}