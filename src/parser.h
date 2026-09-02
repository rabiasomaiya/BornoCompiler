#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "lexer.h"

class Parser {
private:
    std::vector<Token> tokens;
    size_t position;

    Token current();
    void advance();

public:
    Parser(const std::vector<Token>& tokens);

    void parse();
};

#endif