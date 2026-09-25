#ifndef SEMANTIC_H
#define SEMANTIC_H


#include "symbol_table.h"
#include <string>


class SemanticAnalyzer
{

private:

    SymbolTable& table;


public:

    SemanticAnalyzer(SymbolTable& st);



    bool checkDeclaration(
        const std::string& name,
        const std::string& type,
        const std::string& valueType,
        int line
    );



    bool checkAssignment(
        const std::string& name,
        const std::string& valueType,
        int line
    );



    bool checkVariable(
        const std::string& name,
        int line
    );



    bool checkOperation(
        const std::string& leftType,
        const std::string& rightType,
        const std::string& op,
        int line
    );



    bool compatibleType(
        const std::string& expected,
        const std::string& actual
    );



    void error(
        const std::string& message,
        int line
    );


};


#endif