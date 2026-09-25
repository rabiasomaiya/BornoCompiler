#include "intermediate.h"

using namespace std;


IntermediateCodeGenerator::IntermediateCodeGenerator()
{
    tempCount = 0;
    labelCount = 0;
}


string IntermediateCodeGenerator::newTemp()
{
    tempCount++;

    return "t" + to_string(tempCount);
}


string IntermediateCodeGenerator::newLabel()
{
    labelCount++;

    return "L" + to_string(labelCount);
}


void IntermediateCodeGenerator::emit(
    const string& op,
    const string& arg1,
    const string& arg2,
    const string& result
)
{
    Instruction ins;

    ins.op = op;
    ins.arg1 = arg1;
    ins.arg2 = arg2;
    ins.result = result;

    instructions.push_back(ins);
}


const vector<Instruction>&
IntermediateCodeGenerator::getInstructions() const
{
    return instructions;
}


void IntermediateCodeGenerator::print() const
{
    cout << "\n========== INTERMEDIATE CODE ==========\n";


    for(const auto& ins : instructions)
    {

        // Assignment
        if(ins.op == "=")
        {
            cout
                << ins.result
                << " = "
                << ins.arg1
                << "\n";
        }


        // Print
        else if(ins.op == "PRINT")
        {
            cout
                << "PRINT "
                << ins.arg1
                << "\n";
        }


        // Conditional jump
        else if(ins.op == "IF_FALSE")
        {
            cout
                << "IF_FALSE "
                << ins.arg1
                << " GOTO "
                << ins.result
                << "\n";
        }


        // Unconditional jump
        else if(ins.op == "GOTO")
        {
            cout
                << "GOTO "
                << ins.result
                << "\n";
        }


        // Label
        else if(ins.op == "LABEL")
        {
            cout
                << ins.result
                << ":\n";
        }


        // Arithmetic / Comparison
        else
        {
            cout
                << ins.result
                << " = "
                << ins.arg1
                << " "
                << ins.op
                << " "
                << ins.arg2
                << "\n";
        }
    }
}