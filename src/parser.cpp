#include "parser.h"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), position(0) {}

Token Parser::current() {
    return tokens[position];
}

void Parser::advance() {
    if (position < tokens.size()) {
        position++;
    }
}

void Parser::parse() {
    std::cout << "Parser started successfully!" << std::endl;

    while (position < tokens.size()) {
        Token token = current();

        std::cout << "Parsing: "
                  << token.value
                  << std::endl;

        advance();
    }

    std::cout << "Parsing completed!" << std::endl;
}