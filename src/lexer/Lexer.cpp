#include "lexer/Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input)
: Input(input),Position(0)
{

}
char Lexer::peekNext() const{
    if(Position+1>=Input.size())
    {
        return '\0';
    }
    return Input[Position+1];
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
            if(Identifier=="while")
            {
                Tokens.emplace_back(TokenType::While,Identifier);
            }
            else if(Identifier=="if")
            {
                Tokens.emplace_back(TokenType::If,Identifier);

            }
            else if(Identifier=="else")
            {
                Tokens.emplace_back(TokenType::Else,Identifier);

            }
            else if(Identifier=="break")
            {
                Tokens.emplace_back(TokenType::Break,Identifier);
            }
            else if(Identifier=="continue")
            {
                Tokens.emplace_back(TokenType::Continue,Identifier);
            }
            else if(Identifier=="for")
            {
                Tokens.emplace_back(TokenType::For,Identifier);
            }
            else if(Identifier=="return")
            {
                Tokens.emplace_back(TokenType::Return,Identifier);
            }
            else  if(Identifier=="function")
            {
                Tokens.emplace_back(TokenType::Function,Identifier);
            }
            else{
                Tokens.emplace_back(TokenType::Identifier,Identifier);
            }
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
    if(peekNext()=='=')
{
    Tokens.emplace_back(TokenType::EqualEqual,"==");
    Position+=2;
    continue;
}
else
{
    Tokens.emplace_back(TokenType::Equal,"=");
    Position++;
    continue;
}
  
    case ';':
    Tokens.emplace_back(TokenType::SemiColon,";");
    break;
    case '<':
    if(peekNext()=='=')
    {
        Tokens.emplace_back(TokenType::LessEqual,"<=");
        Position+=2;
        continue;
    }
    else{
        Tokens.emplace_back(TokenType::Less,"<");
        Position++;
        continue;
    }
    break;
    case '>':
    {
        if(peekNext()=='=')
    {
        Tokens.emplace_back(TokenType::GreaterEqual,">=");
    Position+=2;
    continue;
    }
    else{
        Tokens.emplace_back(TokenType::Greater,">");
        Position++;
        continue;
    }
    }
    break;
    case '!':
    if(peekNext()=='=')
    {
        Tokens.emplace_back(TokenType::NotEqual,"!=");
        Position+=2;
        continue;
    }
    

    break;
    case '{':
    Tokens.emplace_back(TokenType::LBrace,"{");
    break;

case '}':
    Tokens.emplace_back(TokenType::RBrace,"}");
    break;
case ',':
Tokens.emplace_back(TokenType::Comma,",");
Position++;
break;
    default:
    break;

}
  Position++;

    }

    Tokens.emplace_back(TokenType::End,"");
    return Tokens;
}

