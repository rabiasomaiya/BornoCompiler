#include "lexer.h"
#include <cctype>


Lexer::Lexer(std::string input)
{
    source = input;
    position = 0;
    line = 1;
}


bool Lexer::isKeyword(std::string word)
{
    std::vector<std::string> keywords =
    {
        "সংখ্যা",
        "দশমিক",
        "লেখা",
        "যদি",
        "নাহলে",
        "যতক্ষণ",
        "দেখাও",
        "ফেরত"
    };


    for(auto k : keywords)
    {
        if(word == k)
            return true;
    }

    return false;
}


bool Lexer::isOperator(char c)
{
    return c=='+' ||
           c=='-' ||
           c=='*' ||
           c=='/' ||
           c=='=' ||
           c=='>' ||
           c=='<' ||
           c=='!';
}


bool Lexer::isSymbol(char c)
{
    return c==';' ||
           c=='(' ||
           c==')' ||
           c=='{' ||
           c=='}';
}



std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;


    while(position < source.length())
    {

        char current = source[position];


        if(current==' ' || current=='\t')
        {
            position++;
            continue;
        }


        if(current=='\n')
        {
            line++;
            position++;
            continue;
        }



        // Identifier / Bangla keyword

        if(isalpha((unsigned char)current) ||
           (unsigned char)current >= 128)
        {

            std::string word;


            while(position < source.length() &&
                 (
                  isalnum((unsigned char)source[position]) ||
                  (unsigned char)source[position] >= 128
                 ))
            {
                word += source[position];
                position++;
            }


            if(isKeyword(word))
            {
                tokens.push_back(
                {
                    TokenType::KEYWORD,
                    word,
                    line
                });
            }
            else
            {
                tokens.push_back(
                {
                    TokenType::IDENTIFIER,
                    word,
                    line
                });
            }


            continue;
        }




        // NUMBER + DECIMAL FIX

        if(isdigit(current))
        {

            std::string number;
            bool dot = false;


            while(position < source.length())
            {

                char c = source[position];


                if(isdigit(c))
                {
                    number += c;
                    position++;
                }

                else if(c=='.' && !dot)
                {
                    dot = true;
                    number += c;
                    position++;
                }

                else
                {
                    break;
                }

            }


            tokens.push_back(
            {
                TokenType::NUMBER,
                number,
                line
            });


            continue;
        }




        // STRING

        if(current=='"')
        {

            position++;

            std::string str;


            while(position < source.length()
                  &&
                  source[position]!='"')
            {
                str += source[position];
                position++;
            }


            if(position < source.length())
                position++;


            tokens.push_back(
            {
                TokenType::STRING,
                str,
                line
            });


            continue;
        }




        // OPERATOR + == FIX

        if(isOperator(current))
        {

            std::string op;
            op += current;
            position++;


            if(current=='=' &&
               position < source.length() &&
               source[position]=='=')
            {
                op += '=';
                position++;
            }


            tokens.push_back(
            {
                TokenType::OPERATOR,
                op,
                line
            });


            continue;
        }




        // SYMBOL

        if(isSymbol(current))
        {

            tokens.push_back(
            {
                TokenType::SYMBOL,
                std::string(1,current),
                line
            });


            position++;
            continue;
        }




        // UNKNOWN

        tokens.push_back(
        {
            TokenType::UNKNOWN,
            std::string(1,current),
            line
        });


        position++;

    }


    return tokens;
}