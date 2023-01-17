#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(32);
IntType TypeSystem::commonBool = IntType(1);
VoidType TypeSystem::commonVoid = VoidType();
IntType TypeSystem::commonConstInt = IntType(32, true);
ErrorType TypeSystem::commonError = ErrorType();

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::boolType = &commonBool;
Type* TypeSystem::constIntType = &commonConstInt;
Type* TypeSystem::errorType = &commonError;

std::string IntType::toStr()
{
    // if(isConst())
    // {
    //     return "const int";
    // }
    // else
    // {
    //     return "int";
    // }
    std::ostringstream buffer;
    buffer << "i" << size;
    return buffer.str();
}

std::string VoidType::toStr()
{
    return "void";
}

std::string ErrorType::toStr()
{
    return "Type Error";
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

std::string PointerType::toStr()
{
    std::ostringstream buffer;
    buffer << valueType->toStr() << "*";
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

std::string ArrayType::toStr()
{
    std::ostringstream buffer;
    buffer << "[" << length << " x " << valueType->toStr() << "]";
    return buffer.str();
}