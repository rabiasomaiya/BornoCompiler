#include "parser.h"
#include <iostream>
#include <cctype>
using namespace std;
struct ParseError {};
static string known(string valueType, string expected)
{
    return valueType == "UNKNOWN" ? expected : valueType;
}
Parser::Parser(vector<Token> t, SymbolTable& st)
    : table(st), sem(st)
{
    tokens = t;
}
Token Parser::peek()
{
    if(pos >= tokens.size())
        return {TokenType::UNKNOWN,"EOF",0};

    return tokens[pos];
}
bool Parser::is(string value)
{
    return peek().value == value;
}
void Parser::expect(string value)
{
    if(is(value))
        pos++;

    else
        error("expected '" + value + "'");
}

void Parser::error(string message)
{
    cout
    << "ERROR (line "
    << (pos < tokens.size() ? tokens[pos].line : 0)
    << "): "
    << message
    << "\n";


    errorCount++;

    throw ParseError();
}
void Parser::safeStatement()
{
    size_t start = pos;


    try
    {
        statement();
    }

    catch(ParseError&)
    {

        while(pos < tokens.size()
              &&
              !is(";")
              &&
              !is("}"))
        {
            pos++;
        }


        if(is(";"))
            pos++;


        if(pos == start)
            pos++;

    }
}
void Parser::parse()
{

    while(pos < tokens.size())
        safeStatement();



    if(errorCount > 0)
    {
        cout
        << "\nError ache, tai code generate hobe na.\n";

        return;
    }

    ir.print();

    CodeGenerator(
        ir.getInstructions()
    ).generatePython();

}
void Parser::statement()
{

    if(
        is("সংখ্যা") ||
        is("দশমিক") ||
        is("লেখা")
    )
    {
        declaration();
    }

    else if(is("যদি"))
    {
        ifStatement();
    }

    else if(is("যতক্ষণ"))
    {
        whileStatement();
    }

    else if(is("দেখাও"))
    {
        printStatement();
    }

    else if(is("{"))
    {
        block();
    }

    else if(peek().type == TokenType::IDENTIFIER)
    {
        assignment();
    }

    else
    {
        error("unexpected token " + peek().value);
    }

}
void Parser::declaration()
{

    int line = peek().line;


    string type = tokens[pos++].value;


    if(peek().type != TokenType::IDENTIFIER)
        error("variable name expected");


    string name = tokens[pos++].value;
    expect("=");
    Expr value = expression();
    expect(";");
    if(
        !sem.checkDeclaration(
            name,
            type,
            known(value.type,type),
            line
        )
    )
    {
        errorCount++;
    }
    cout
    << "DECLARE : "
    << type
    << " "
    << name
    << "\n";
    ir.emit(
        "=",
        value.place,
        "",
        name
    );

}
void Parser::assignment()
{

    int line = peek().line;
    string name = tokens[pos++].value;
    expect("=");
    Expr value = expression();
    expect(";");
    if(
        !sem.checkAssignment(
            name,
            known(
                value.type,
                table.typeOf(name)
            ),
            line
        )
    )
    {
        errorCount++;
    }
    cout
    << "ASSIGN : "
    << name
    << "\n";
    ir.emit(
        "=",
        value.place,
        "",
        name
    );

}
void Parser::ifStatement()
{

    pos++;
    expect("(");
    Expr cond = expression();
    expect(")");
    string elseLabel =
        ir.newLabel();
    ir.emit(
        "IF_FALSE",
        cond.place,
        "",
        elseLabel
    );
    block();
    if(is("নাহলে"))
    {
        pos++;
        string endLabel =
            ir.newLabel();
        ir.emit(
            "GOTO",
            "",
            "",
            endLabel
        );
        ir.emit(
            "LABEL",
            "",
            "",
            elseLabel
        );
        block();
        ir.emit(
            "LABEL",
            "",
            "",
            endLabel
        );

    }

    else
    {

        ir.emit(
            "LABEL",
            "",
            "",
            elseLabel
        );

    }

}
void Parser::whileStatement()
{
    pos++;
    string start =
        ir.newLabel();
    string end =
        ir.newLabel();
    ir.emit(
        "LABEL",
        "",
        "",
        start
    );
    expect("(");
    Expr cond =
        expression();
    expect(")");
    ir.emit(
        "IF_FALSE",
        cond.place,
        "",
        end
    );
    block();
    ir.emit(
        "GOTO",
        "",
        "",
        start
    );
    ir.emit(
        "LABEL",
        "",
        "",
        end
    );

}
void Parser::printStatement()
{
    pos++;
    expect("(");
    Expr value =
        expression();
    expect(")");
    expect(";");
    ir.emit(
        "PRINT",
        value.place,
        "",
        ""
    );

}
void Parser::block()
{
    expect("{");
    while(
        pos < tokens.size()
        &&
        !is("}")
    )
    {
        safeStatement();
    }
    expect("}");

}
Expr Parser::binary(
    Expr left,
    string op,
    Expr right
)
{
    if(
        !sem.checkOperation(
            left.type,
            right.type,
            op,
            tokens[pos-1].line
        )
    )
    {
        errorCount++;
    }
    string temp =
        ir.newTemp();
    ir.emit(
        op,
        left.place,
        right.place,
        temp
    );
    string type;
    if(
        op==">" ||
        op=="<" ||
        op=="=="
    )
    {
        type="BOOLEAN";
    }
    else if(
        left.type=="দশমিক" ||
        right.type=="দশমিক"
    )
    {
        type="দশমিক";
    }
    else
    {
        type="সংখ্যা";
    }
    return {temp,type};

}
Expr Parser::expression()
{

    Expr left =
        term();

    if(
        is(">") ||
        is("<") ||
        is("==")
    )
    {
        string op =
            tokens[pos++].value;
        Expr right =
            term();
        left =
            binary(
                left,
                op,
                right
            );
    }
    return left;
}
Expr Parser::term()
{
    Expr left =
        factor();
    while(
        is("+") ||
        is("-")
    )
    {
        string op =
            tokens[pos++].value;
        left =
            binary(
                left,
                op,
                factor()
            );

    }
    return left;

}
Expr Parser::factor()
{

    Expr left =
        primary();
    while(
        is("*") ||
        is("/")
    )
    {

        string op =
            tokens[pos++].value;
        left =
            binary(
                left,
                op,
                primary()
            );

    }
    return left;

}
Expr Parser::primary()
{

    Token t =
        peek();
    if(t.type == TokenType::NUMBER)
    {

        pos++;
        return {
            t.value,
            t.value.find('.') != string::npos
            ?
            "দশমিক"
            :
            "সংখ্যা"
        };

    }
    if(t.type == TokenType::STRING)
    {

        pos++;
        return {
            "\"" + t.value + "\"",
            "লেখা"
        };

    }
    if(t.type == TokenType::IDENTIFIER)
    {

        pos++;
        if(
            !sem.checkVariable(
                t.value,
                t.line
            )
        )
        {
            errorCount++;
        }
        return {
            t.value,
            table.typeOf(t.value)
        };

    }
    if(is("("))
    {

        pos++;
        Expr inside =
            expression();

        expect(")");
        return inside;

    }
    error("value expected");
    return {};
}