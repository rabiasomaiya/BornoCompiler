#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    STRING,
    OPERATOR,
    SYMBOL,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
};

class Lexer {
private:
    std::string source;
    size_t position;
    int line;

public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();
};

#endif