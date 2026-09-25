#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "parser.h"
#include "symbol_table.h"
#include <cstdlib>

using namespace std;

string tokenName(TokenType type)
{
    switch (type)
    {
        case TokenType::KEYWORD:    return "KEYWORD";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::NUMBER:     return "NUMBER";
        case TokenType::STRING:     return "STRING";
        case TokenType::OPERATOR:   return "OPERATOR";
        case TokenType::SYMBOL:     return "SYMBOL";
        default:                    return "UNKNOWN";
    }
}

int main(int argc, char* argv[])
{
#ifdef _WIN32
    system("chcp 65001 > nul");    // terminal e Bangla dekhanor jonno
#endif

    if (argc < 2)
    {
        cout << "Usage: borno.exe <file.bn>\n";
        return 1;
    }

    // File theke code pori
    ifstream file(argv[1]);
    stringstream buffer;
    buffer << file.rdbuf();
    string code = buffer.str();

    // UTF-8 BOM thakle bad dei
    if (code.size() >= 3 && code.substr(0, 3) == "\xEF\xBB\xBF")
        code = code.substr(3);

    // ========== 1. LEXER ==========
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();

    cout << "========== LEXER OUTPUT ==========\n";
    for (auto& t : tokens)
    {
        if (t.value == "\r") continue;   // Windows er faka token dekhai na
        cout << "Line: " << t.line << " | " << tokenName(t.type) << " | " << t.value << "\n";
    }

    // ========== 2. PARSER ==========
    cout << "\n========== PARSER OUTPUT ==========\n";
    SymbolTable table;
    Parser parser(tokens, table);
    parser.parse();

    // ========== 3. SYMBOL TABLE ==========
    table.print();

    cout << "\nTotal errors: " << parser.errorCount << "\n";
    return 0;
}
