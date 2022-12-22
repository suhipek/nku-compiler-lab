#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include <vector>
#include "Type.h"
#include "Operand.h"

#define BEG_BLUE fprintf(stderr, "\033[34m")
#define BEG_RED fprintf(stderr, "\033[31m")
#define END_COLOR fprintf(stderr, "\033[39m")

class SymbolEntry;
class Unit;
class Function;
class BasicBlock;
class Instruction;
class IRBuilder;

class Node
{
private:
    static int counter;
    int seq;
protected:
    int lineno;
    std::vector<Instruction*> true_list;
    std::vector<Instruction*> false_list;
    static IRBuilder *builder;
    void backPatch(std::vector<Instruction*> &list, BasicBlock*bb);
    std::vector<Instruction*> merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2);

public:
    Node();
    int getSeq() const {return seq;};
    static void setIRBuilder(IRBuilder*ib) {builder = ib;};
    virtual void output(int level) = 0;
    virtual Type* typeCheck(Type* retType=nullptr) = 0;
    virtual void genCode() = 0;
    std::vector<Instruction*>& trueList() {return true_list;}
    std::vector<Instruction*>& falseList() {return false_list;}
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
    Operand *dst;   // The result of the subtree is stored into dst.
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){dst = new Operand(symbolEntry);};
    Operand* getOperand() {return dst;};
    SymbolEntry* getSymPtr() {return symbolEntry;};
    virtual void genBr() = 0;
};

class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD, SUB, AND, MUL, DIV, MOD, OR, LESS, GREATER, EQ, NEQ, LEQ, GEQ};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){dst = new Operand(se);};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
    void genBr();
};

class UnaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr;
public:
    enum{NOT, SUB};
    UnaryExpr(SymbolEntry *se, int op, ExprNode *expr) : ExprNode(se), op(op), expr(expr){};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
    void genBr();
};

class ConvExpr : public ExprNode
{
private:
    Type *type;
    ExprNode *expr;
public:
    ConvExpr(SymbolEntry *se, Type *type, ExprNode *expr) : ExprNode(se), type(type), expr(expr){dst = new Operand(se);};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
    void genBr(){}
};

class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){dst = new Operand(se);};
    void output(int level);
    std::string getValue() {return symbolEntry->toStr();};
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
    void genBr(){}
};

class Id : public ExprNode
{
public:
    Id(SymbolEntry *se) : ExprNode(se){SymbolEntry *temp = new TemporarySymbolEntry(se->getType(), SymbolTable::getLabel()); dst = new Operand(temp);};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
    void genBr(){}
};

class StmtNode : public Node
{};

class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt) : stmt(stmt) {};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
};

class DeclStmt : public StmtNode
{
private:
    Id *id;
    ExprNode *expr;
public:
    DeclStmt(Id *id) : id(id), expr(nullptr){};
    DeclStmt(Id *id, ExprNode *expr) : id(id), expr(expr){};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
    void genCodeAsFuncArg(Operand* arg);
    SymbolEntry *getSymPtr() {return id->getSymPtr();}

};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
};

class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
};

class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *body;
public:
    WhileStmt(ExprNode *cond, StmtNode *body) : cond(cond), body(body){};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr); // unfinished
    void genCode(); // unfinished
};

class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
    static int check_cnt; // 类型检查计数器
public:
    ReturnStmt(ExprNode*retValue) : retValue(retValue) {};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
    static const int getCheckCnt() {return check_cnt;}
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
};

class ExprStmt : public StmtNode
{
private:
    ExprNode *expr;
public:
    ExprStmt(ExprNode *expr) : expr(expr) {};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
};

class FuncParams : public Node
{
private:
    std::vector<Type *> types;
    std::vector<DeclStmt*> decls;
public:
    FuncParams(){}
    void append(Type*, DeclStmt*);
    std::vector<Type *> getTypes() const {return types;};
    void output(int level);
    Type* typeCheck(Type* retType=nullptr) {return nullptr;} // 不需要
    std::vector<DeclStmt*> getDecls() const {return decls;} // 获取参数列表DeclStmt
    void genCode() {} // 不需要，话说当时就不该这么实现函数参数
};

class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    FuncParams *params;
    StmtNode *stmt;  
public:
    FunctionDef *next;
    FunctionDef(SymbolEntry *se, FuncParams *params, StmtNode *stmt) : 
        se(se), params(params), stmt(stmt), next(nullptr){};
    void setStmt(StmtNode *stmt){this->stmt = stmt;} // for function prototype
    void output(int level);
    std::vector<Type *> getFormalTypes() {return params->getTypes();}
    SymbolEntry *getSymPtr() {return se;}
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
};

class CallParams : public Node
{
protected:
    std::vector<ExprNode*> params;
public:
    CallParams(){}
    void append(ExprNode* expr);
    void output(int level);
    Type* typeCheck(Type* retType=nullptr) {return nullptr;} // 不需要
    void genCode() {} // 不需要，话说当时就不该这么实现函数参数
    friend class CallExpr;
};

class CallExpr : public ExprNode
{
protected:
    CallParams* params; // argument list
public:
    CallExpr(SymbolEntry *se, CallParams* params) : ExprNode(se), params(params){
        dst = new Operand(new TemporarySymbolEntry(
                ((FunctionType *)(symbolEntry->getType()))->getRetType(), 
                SymbolTable::getLabel()));
    }
    void output(int level);
    Type* typeCheck(Type* retType=nullptr);
    void genCode();
    void genBr(){}
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
    Type* typeCheck(Type* retType=nullptr);
    void genCode(Unit *unit);
};

#endif
