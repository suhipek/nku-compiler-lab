#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(4);
VoidType TypeSystem::commonVoid = VoidType();

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;

std::string IntType::toStr()
{
    return "int";
}

std::string VoidType::toStr()
{
    return "void";
}

std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "(";
    // for(auto it: paramsType) 为啥auto会被推倒成Type*
    for(auto it = paramsType.begin(); it != paramsType.end(); ++it)
    {
        buffer << (*it)->toStr();
        if(it != paramsType.end() - 1)
            buffer << ", ";
    }
    buffer << ")";
    return buffer.str();
}
