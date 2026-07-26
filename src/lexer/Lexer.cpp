#include "lexer/Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input)
: Input(input),Position(0)
{

}
std::vector<Token>Lexer::tokenize()
{
   
    std::vector<Token>Tokens;
    while(Position<Input.size())
    {
        char Current=Input[Position];
        if(isspace(Current))
        {
            Position++;
            continue;
        }
        if(isdigit(Current))
        {
            std::string Number;
            while (Position < Input.size() &&
       isdigit(Input[Position]))
{
    Number += Input[Position];
    Position++;
}
Tokens.emplace_back(TokenType::Number,Number);
continue;

        }
        if(isalpha(Current)||Current=='_')
        {
            std::string Identifier;
            while(Position<Input.size()&&(isalnum(Input[Position])||Input[Position]=='_')){
                Identifier+=Input[Position];
                Position++;
                
            }
            Tokens.emplace_back(TokenType::Identifier,Identifier);
            continue;
        }
      
switch(Current)
{
    case '+':
    Tokens.emplace_back(TokenType::Plus,"+");
    break;
    case '-':
    Tokens.emplace_back(TokenType::Minus,"-");
    break;
    case '*':
    Tokens.emplace_back(TokenType::Star,"*");
    break;
    case '/':
    Tokens.emplace_back(TokenType::Slash,"/");
    break;
    case '(':
    Tokens.emplace_back(TokenType::LParen,"(");
    break;
    case ')':
    Tokens.emplace_back(TokenType::RParen,")");
    break;
    case '=':
    Tokens.emplace_back(TokenType::Equal,"=");
    break;
    default:
    break;
}
  Position++;

    }
  
Tokens.emplace_back(TokenType::End, "");
return Tokens;
}