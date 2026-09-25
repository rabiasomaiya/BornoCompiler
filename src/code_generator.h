#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "intermediate.h"
#include <vector>
#include <string>

class CodeGenerator
{
private:
    const std::vector<Instruction>& instructions;

public:
    CodeGenerator(
        const std::vector<Instruction>& code
    );

    void generatePython() const;
};

#endif