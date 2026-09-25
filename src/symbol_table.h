#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct SymbolEntry
{
    int serial;
    std::string name;
    std::string dataType;
    std::string scope;
    int declaredLine;
    int address;
};

class SymbolTable
{
private:
    std::vector<SymbolEntry> symbols;
    int nextAddress = 1000;

public:

    bool exists(const std::string& name) const
    {
        for (const auto& symbol : symbols)
        {
            if (symbol.name == name)
                return true;
        }

        return false;
    }

    bool add(const std::string& name,
             const std::string& dataType,
             int declaredLine)
    {
        if (exists(name))
        {
            std::cout
                << "SEMANTIC ERROR (line "
                << declaredLine
                << "): Variable '"
                << name
                << "' is already declared.\n";

            return false;
        }

        SymbolEntry newSymbol;

        newSymbol.serial =
            static_cast<int>(symbols.size()) + 1;

        newSymbol.name = name;
        newSymbol.dataType = dataType;
        newSymbol.scope = "Global";
        newSymbol.declaredLine = declaredLine;
        newSymbol.address = nextAddress;

        symbols.push_back(newSymbol);

        nextAddress += 4;

        return true;
    }

    std::string typeOf(const std::string& name) const
    {
        for (const auto& symbol : symbols)
        {
            if (symbol.name == name)
                return symbol.dataType;
        }

        return "UNKNOWN";
    }

    void print() const
    {
        std::cout << "\nSYMBOL TABLE\n";

        std::cout
            << "------------------------------------------------------------------\n";

        std::cout
            << std::left
            << std::setw(5)  << "SL"
            << std::setw(18) << "IDENTIFIER"
            << std::setw(18) << "DATA TYPE"
            << std::setw(12) << "SCOPE"
            << std::setw(8)  << "LINE"
            << "ADDRESS\n";

        std::cout
            << "------------------------------------------------------------------\n";

        if (symbols.empty())
        {
            std::cout << "No identifier found.\n";
        }
        else
        {
            for (const auto& symbol : symbols)
            {
                std::cout
                    << std::left
                    << std::setw(5)  << symbol.serial
                    << std::setw(18) << symbol.name
                    << std::setw(18) << symbol.dataType
                    << std::setw(12) << symbol.scope
                    << std::setw(8)  << symbol.declaredLine
                    << symbol.address
                    << '\n';
            }
        }

        std::cout
            << "------------------------------------------------------------------\n";
    }
};

#endif