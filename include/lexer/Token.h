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
    EqualEqual,
    NotEqual,
    LessEqual,
    GreaterEqual,
    Greater,
    Less,
    SemiColon,
    LBrace,
    RBrace,
    If,
    Else,
    While,
    Break,
    Continue,
    For,
    Return,
    Function,
    Comma,
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