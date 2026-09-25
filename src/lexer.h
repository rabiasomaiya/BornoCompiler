#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>

enum class TokenType
{
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    STRING,
    OPERATOR,
    SYMBOL,
    UNKNOWN
};


struct Token
{
    TokenType type;
    std::string value;
    int line;
};


class Lexer
{

private:

    std::string source;
    size_t position;
    int line;


    bool isKeyword(std::string word);

    bool isOperator(char c);

    bool isSymbol(char c);


public:

    Lexer(std::string input);

    std::vector<Token> tokenize();

};


#endif