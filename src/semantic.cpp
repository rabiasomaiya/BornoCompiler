#include "semantic.h"
#include <iostream>


using namespace std;



SemanticAnalyzer::SemanticAnalyzer(SymbolTable& st)
    : table(st)
{

}




bool SemanticAnalyzer::compatibleType(
    const string& expected,
    const string& actual
)
{


    if(expected == actual)
        return true;



    // দশমিক can accept সংখ্যা

    if(
        expected=="দশমিক" &&
        actual=="সংখ্যা"
    )
        return true;



    return false;

}






bool SemanticAnalyzer::checkDeclaration(
    const string& name,
    const string& type,
    const string& valueType,
    int line
)
{


    if(table.exists(name))
    {

        error(
        "Variable '"+name+"' already declared",
        line
        );


        return false;

    }



    if(!compatibleType(type,valueType))
    {

        error(
        "Cannot assign "
        +valueType+
        " to "
        +type,
        line
        );


        return false;

    }



    return table.add(
        name,
        type,
        line
    );

}







bool SemanticAnalyzer::checkAssignment(
    const string& name,
    const string& valueType,
    int line
)
{


    if(!table.exists(name))
    {

        error(
        "Variable '"+name+"' is not declared",
        line
        );


        return false;

    }



    string currentType =
        table.typeOf(name);



    if(!compatibleType(
        currentType,
        valueType
    ))
    {

        error(
        "Type mismatch: cannot assign "
        +valueType+
        " to "
        +currentType,
        line
        );


        return false;

    }



    return true;

}








bool SemanticAnalyzer::checkVariable(
    const string& name,
    int line
)
{


    if(!table.exists(name))
    {

        error(
        "Undeclared variable '"+name+"'",
        line
        );


        return false;

    }


    return true;

}







bool SemanticAnalyzer::checkOperation(
    const string& leftType,
    const string& rightType,
    const string& op,
    int line
)
{


    if(
        op=="+" ||
        op=="-" ||
        op=="*" ||
        op=="/"
    )
    {


        if(
            leftType!="সংখ্যা" &&
            leftType!="দশমিক"
        )
        {

            error(
            "Invalid left operand",
            line
            );

            return false;

        }



        if(
            rightType!="সংখ্যা" &&
            rightType!="দশমিক"
        )
        {

            error(
            "Invalid right operand",
            line
            );

            return false;

        }


    }


    return true;

}








void SemanticAnalyzer::error(
    const string& message,
    int line
)
{

    cout
    <<"SEMANTIC ERROR (line "
    <<line
    <<"): "
    <<message
    <<endl;

}