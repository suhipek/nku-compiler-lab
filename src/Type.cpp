#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(4);
VoidType TypeSystem::commonVoid = VoidType();
IntType TypeSystem::commonConstInt = IntType(4, true);

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::constIntType = &commonConstInt;

std::string IntType::toStr()
{
    if(isConst())
    {
        return "const int";
    }
    else
    {
        return "int";
    }
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


Type* TypeSystem::getConstTypeOf(Type *type)
{
    if(type->isInt())
    {
        return constIntType;
    }
    else
    {
        return type;
    }
}