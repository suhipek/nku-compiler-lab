#ifndef __TYPE_H__
#define __TYPE_H__
#include <vector>
#include <string>

class Type
{
private:
    int kind;
    bool isConstType;
protected:
    enum {INT, VOID, FUNC, PTR};
public:
    Type(int kind, bool _isConst = false) : kind(kind), isConstType(_isConst) {};
    virtual ~Type() {};
    virtual std::string toStr() = 0;
    bool isInt() const {return kind == INT;};
    bool isVoid() const {return kind == VOID;};
    bool isFunc() const {return kind == FUNC;};
    bool isConst() const {return isConstType;};
};

class IntType : public Type
{
private:
    int size;
public:
    IntType(int size, bool isConst = false) : Type(Type::INT, isConst), size(size){};
    std::string toStr();
};

class VoidType : public Type
{
public:
    VoidType() : Type(Type::VOID){};
    std::string toStr();
};

class FunctionType : public Type
{
private:
    Type *returnType;
    std::vector<Type*> paramsType;
public:
    FunctionType(Type* returnType, std::vector<Type*> paramsType) : 
        Type(Type::FUNC), returnType(returnType), paramsType(paramsType){};
    Type* getRetType() {return returnType;};
    std::vector<Type*> getParamsType() {return paramsType;};
    std::string toStr();
};

class PointerType : public Type
{
private:
    Type *valueType;
public:
    PointerType(Type* valueType) : Type(Type::PTR) {this->valueType = valueType;};
    Type* getValueType() {return valueType;};
    std::string toStr();
};

class ArrayType : public Type
{
private:
    Type *valueType;
    int size;
public:
    ArrayType(Type* valueType, int size) : Type(Type::PTR), size(size) {this->valueType = valueType;};
    Type* getValueType() {return valueType;};
    int getSize() {return size;};
    std::string toStr();
};

class ErrorType : public Type
{
public:
    ErrorType() : Type(Type::VOID){};
    std::string toStr();
};

class TypeSystem
{
private:
    static IntType commonInt;
    static IntType commonBool;
    static VoidType commonVoid;
    static IntType commonConstInt;
    static ErrorType commonError;
public:
    static Type *intType;
    static Type *voidType;
    static Type *constIntType;
    static Type *getConstTypeOf(Type *type);
    static Type *boolType;
    static Type *errorType;
};

#endif
