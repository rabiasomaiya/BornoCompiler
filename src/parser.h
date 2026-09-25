#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "symbol_table.h"
#include "intermediate.h"
#include "code_generator.h"
#include "semantic.h"

struct Expr
{
    std::string place;   // result kothay: t1, a, 10
    std::string type;    // সংখ্যা / দশমিক / লেখা
};

class Parser
{
public:
    std::vector<Token> tokens;
    size_t pos = 0;
    int errorCount = 0;
    SymbolTable& table;
    IntermediateCodeGenerator ir;
    SemanticAnalyzer sem;           // type checking

    Parser(std::vector<Token> tokens, SymbolTable& table);
    void parse();
    Token peek();                   bool is(std::string value);
    void expect(std::string value); void error(std::string message);
    void safeStatement();

    // grammar rules
    void statement();      void declaration();    void assignment();
    void ifStatement();    void whileStatement(); void printStatement();
    void block();
    Expr expression(); Expr term(); Expr factor(); Expr primary();
    Expr binary(Expr left, std::string op, Expr right);
};

#endif
