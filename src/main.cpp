#include <iostream>
#include <iomanip>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "symbol_table.h"



std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::KEYWORD:
            return "KEYWORD";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::NUMBER:
            return "NUMBER";
        case TokenType::STRING:
            return "STRING";
        case TokenType::OPERATOR:
            return "OPERATOR";
        case TokenType::SYMBOL:
            return "SYMBOL";
        default:
            return "UNKNOWN";
    }
}

int main() {
    std::string code =
        "সংখ্যা x = 10;\n"
        "সংখ্যা y = 20;\n"
        "লেখা name = \"Somaiya\";\n"
        "x = x + y;\n";

    Lexer lexer(code);

    std::vector<Token> tokens = lexer.tokenize();
    
    SymbolTable symbolTable;

for (const auto& token : tokens) {
    if (token.type == TokenType::IDENTIFIER) {
        symbolTable.add(token.value, "IDENTIFIER", token.line);
    }
}

    Parser parser(tokens);
    parser.parse();

    std::cout << std::left
              << std::setw(15) << "TOKEN"
              << std::setw(20) << "VALUE"
              << "LINE"
              << std::endl;

    std::cout << "---------------------------------------------\n";

    for (const Token& token : tokens) {
        std::cout << std::left
                  << std::setw(15) << tokenTypeToString(token.type)
                  << std::setw(20) << token.value
                  << token.line
                  << std::endl;
    }
    
    symbolTable.print();
    return 0;
}