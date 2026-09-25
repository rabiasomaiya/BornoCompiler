#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include <iostream>
#include <string>
#include <vector>

struct Instruction
{
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
};

class IntermediateCodeGenerator
{
private:
    std::vector<Instruction> instructions;

    int tempCount;
    int labelCount;

public:
    IntermediateCodeGenerator();

    std::string newTemp();

    std::string newLabel();

    void emit(
        const std::string& op,
        const std::string& arg1,
        const std::string& arg2,
        const std::string& result
    );

    const std::vector<Instruction>& getInstructions() const;

    void print() const;
};

#endif