#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

struct SymbolInfo {
    std::string name;
    std::string type;
    int line;
};

class SymbolTable {
private:
    std::vector<SymbolInfo> symbols;

public:
    void add(const std::string& name,
             const std::string& type,
             int line) {

        // একই identifier বারবার add না করার জন্য
        for (const auto& symbol : symbols) {
            if (symbol.name == name) {
                return;
            }
        }

        symbols.push_back({name, type, line});
    }

    void print() const {
        std::cout << "\nSYMBOL TABLE\n";
        std::cout << std::left
                  << std::setw(20) << "NAME"
                  << std::setw(20) << "TYPE"
                  << "LINE\n";

        std::cout << "---------------------------------------------\n";

        for (const auto& symbol : symbols) {
            std::cout << std::left
                      << std::setw(20) << symbol.name
                      << std::setw(20) << symbol.type
                      << symbol.line << '\n';
        }
    }
};

#endif