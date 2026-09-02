#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& source) {
    this->source = source;
    position = 0;
    line = 1;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (position < source.size()) {

        char current = source[position];

        // New line
        if (current == '\n') {
            line++;
            position++;
            continue;
        }

        // Space / tab
        if (std::isspace(static_cast<unsigned char>(current))) {
            position++;
            continue;
        }

        // Bangla Keywords
        std::vector<std::string> keywords = {
            "সংখ্যা",
            "লেখা",
            "যদি",
            "নাহলে",
            "যতক্ষণ",
            "দেখাও"
        };

        bool keywordFound = false;

        for (const std::string& keyword : keywords) {
            if (source.compare(position, keyword.size(), keyword) == 0) {
                tokens.push_back({
                    TokenType::KEYWORD,
                    keyword,
                    line
                });

                position += keyword.size();
                keywordFound = true;
                break;
            }
        }

        if (keywordFound)
            continue;

        // Number
        if (std::isdigit(static_cast<unsigned char>(current))) {
            std::string number;

            while (
                position < source.size() &&
                std::isdigit(static_cast<unsigned char>(source[position]))
            ) {
                number += source[position];
                position++;
            }

            tokens.push_back({
                TokenType::NUMBER,
                number,
                line
            });

            continue;
        }

        // English Identifier
        if (
            std::isalpha(static_cast<unsigned char>(current)) ||
            current == '_'
        ) {
            std::string identifier;

            while (
                position < source.size() &&
                (
                    std::isalnum(static_cast<unsigned char>(source[position])) ||
                    source[position] == '_'
                )
            ) {
                identifier += source[position];
                position++;
            }

            tokens.push_back({
                TokenType::IDENTIFIER,
                identifier,
                line
            });

            continue;
        }

        // String
        if (current == '"') {
            position++;

            std::string value;

            while (
                position < source.size() &&
                source[position] != '"'
            ) {
                value += source[position];

                if (source[position] == '\n')
                    line++;

                position++;
            }

            if (
                position < source.size() &&
                source[position] == '"'
            ) {
                position++;
            }

            tokens.push_back({
                TokenType::STRING,
                value,
                line
            });

            continue;
        }

        // Operators
        if (
            current == '+' ||
            current == '-' ||
            current == '*' ||
            current == '/' ||
            current == '=' ||
            current == '<' ||
            current == '>'
        ) {
            tokens.push_back({
                TokenType::OPERATOR,
                std::string(1, current),
                line
            });

            position++;
            continue;
        }

        // Symbols
        if (
            current == ';' ||
            current == '(' ||
            current == ')' ||
            current == '{' ||
            current == '}'
        ) {
            tokens.push_back({
                TokenType::SYMBOL,
                std::string(1, current),
                line
            });

            position++;
            continue;
        }

        // Unknown
        tokens.push_back({
            TokenType::UNKNOWN,
            std::string(1, current),
            line
        });

        position++;
    }

    return tokens;
}