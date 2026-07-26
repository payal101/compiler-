#pragma once
#include<vector>
#include<string>
#include "lexer/Token.h"

class Lexer{
    public:
    Lexer(const std::string&input);
    std::vector<Token> tokenize();

    private:
    std::string Input;
    size_t Position=0;
};