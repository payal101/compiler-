#pragma once
#include <string>
enum class TokenType{
    Number,
    Plus,
    Minus,
    Star,
    Slash,
    LParen,
    RParen,
    Identifier,
    Equal,
    End
};

struct  Token
{
    TokenType Type;
    std::string Text;
    Token(TokenType type,const std::string&text)
    :Type(type),Text(text)
    {
        
    }
};