#include "Operand.h"
#include <sstream>
#include <algorithm>
#include <string.h>
#include <Ast.h>

std::string Operand::toStr() const
{
    return se->toStr();
}

void Operand::removeUse(Instruction *inst)
{
    auto i = std::find(uses.begin(), uses.end(), inst);
    if(i != uses.end())
        uses.erase(i);
}

int Operand::getConstValue(bool *success)
{
    
    if(se->isConstant())
        return ((ConstantSymbolEntry*)se)->getValue();
    else if(se->isVariable())
        return ((IdentifierSymbolEntry*)se)->constInit->getConstExpVal(success);
    *success = false;
    return 0;
}