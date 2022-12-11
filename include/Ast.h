#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include <vector>
#include "Type.h"

class SymbolEntry;

class Node
{
private:
    static int counter;
    int seq;
public:
    Node();
    int getSeq() const {return seq;};
    virtual void output(int level) = 0;
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){};
};

class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD, SUB, AND, MUL, DIV, OR, LESS, GREATER, EQ, NEQ, LEQ, GEQ};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){};
    void output(int level);
};

class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){};
    void output(int level);
};

class Id : public ExprNode
{
public:
    Id(SymbolEntry *se) : ExprNode(se){};
    void output(int level);
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
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
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
};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
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
};

class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *body;
public:
    WhileStmt(ExprNode *cond, StmtNode *body) : cond(cond), body(body){};
    void output(int level);
};

class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue) : retValue(retValue) {};
    void output(int level);
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
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
};

class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    FuncParams *params;
    StmtNode *stmt;
public:
    FunctionDef(SymbolEntry *se, FuncParams *params, StmtNode *stmt) : se(se), params(params), stmt(stmt){};
    void setStmt(StmtNode *stmt){this->stmt = stmt;} // for function prototype
    void output(int level);
};

class CallParams : public Node
{
protected:
    std::vector<ExprNode*> params;
public:
    CallParams(){}
    void append(ExprNode* expr);
    void output(int level);
};

class CallExpr : public ExprNode
{
protected:
    CallParams* params; // argument list
public:
    CallExpr(SymbolEntry *se, CallParams* params) : ExprNode(se), params(params){};
    void output(int level);
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
};

#endif
