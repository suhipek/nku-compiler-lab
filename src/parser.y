%code top{
    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );
    int yyget_lineno(void);
    Type* nowType; // “最近”的类型，用于声明变量
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
    CallParams* callparamstype;
    FuncParams* funcparamstype;
    Node* nodetype;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token IF ELSE WHILE FOR
%token HEX OCT
%token INT VOID
%token CONST
%token COMMA
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON
%token ADD SUB OR AND STAR DIV 
%token LESS GREATER EQ NEQ LEQ GEQ LE GE
%token ASSIGN
%token RETURN

%nterm <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt ReturnStmt DeclStmt FuncDef WhileStmt
%nterm <stmttype> VarList ConstList VarDef ConstDef
%nterm <exprtype> Exp AddExp Cond LOrExp PrimaryExp LVal RelExp LAndExp CallExp MulExp
%nterm <callparamstype> CallParam // 这么写是不是有点割裂。。。算了，先这样吧
%nterm <funcparamstype> FuncParam // #define PHILOSOPHY 能跑就行
%nterm <type> Type

%precedence THEN
%precedence ELSE
%%
Program
    : Stmts {
        ast.setRoot($1);
    }
    ;
Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        $$ = new SeqNode($1, $2);
    }
    ;
Stmt
    : AssignStmt {$$=$1;}
    | BlockStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | FuncDef {$$=$1;}
    | WhileStmt {$$=$1;}
    ;
LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se);
        delete []$1;
    }
    ;
AssignStmt
    :
    LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    |
    CallExp SEMICOLON {
        $$ = new AssignStmt(nullptr, $1);
    }
    ;
BlockStmt
    :   LBRACE 
        {identifiers = new SymbolTable(identifiers);} 
        Stmts RBRACE 
        {
            $$ = new CompoundStmt($3);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
        |
        SEMICOLON
        {
            $$ = new CompoundStmt(nullptr);
        }
    ;
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;
WhileStmt
    : WHILE LPAREN Cond RPAREN Stmt {
        $$ = new WhileStmt($3, $5);
    }
    ;
ReturnStmt
    :
    RETURN Exp SEMICOLON{
        $$ = new ReturnStmt($2);
    }
    ;
Exp
    :
    AddExp {$$ = $1;}
    ;
Cond
    :
    LOrExp {$$ = $1;}
    ;
PrimaryExp
    :
    LVal {
        $$ = $1;
    }
    | INTEGER {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, $1);
        $$ = new Constant(se);
    }
    | CallExp {
        $$ = $1;
    }
    ;
CallExp
    :
    ID LPAREN CallParam RPAREN {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "function \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new CallExpr(se, $3);
        delete []$1;
    }
    ;
CallParam
    :
    %empty {$$ = new CallParams();} // no parameters
    |
    Exp {
        $$ = new CallParams();
        $$->append($1);
    }
    | CallParam COMMA Exp {
        $$->append($3);
    }
    ;
MulExp
    :
    PrimaryExp {$$ = $1;}
    |
    MulExp STAR PrimaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
    }
    |
    MulExp DIV PrimaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
    }
    ;
AddExp
    :
    MulExp {$$ = $1;}
    |
    AddExp ADD MulExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
    }
    |
    AddExp SUB MulExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
    }
    ;
// LESS, GREATER, EQ, NEQ, LEQ, GEQ, LE, GE
RelExp
    :
    AddExp {$$ = $1;}
    |
    RelExp LESS AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    |
    RelExp GREATER AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATER, $1, $3);
    }
    |
    RelExp EQ AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQ, $1, $3);
    }
    |
    RelExp NEQ AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NEQ, $1, $3);
    }
    |
    RelExp LEQ AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LEQ, $1, $3);
    }
    |
    RelExp GEQ AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GEQ, $1, $3);
    }
    ;
LAndExp
    :
    RelExp {$$ = $1;}
    |
    LAndExp AND RelExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
    }
    ;
LOrExp
    :
    LAndExp {$$ = $1;}
    |
    LOrExp OR LAndExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
    }
    ;
Type
    : INT {
        nowType = TypeSystem::intType;
        $$ = TypeSystem::intType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
    }
    ;



DeclStmt
    :
    Type VarList SEMICOLON {
        $$ = $2;
    }
    |
    CONST Type ConstList SEMICOLON {
        $$ = $3;
    }
    ;
VarList
    :
    VarDef {
        $$ = $1;
    }
    |
    VarList COMMA VarDef {
        $$ = new SeqNode($1, $3);
    }
    ;
ConstList
    :
    ConstDef {
        $$ = $1;
    }
    |
    ConstList COMMA ConstDef {
        $$ = new SeqNode($1, $3);
    }
    ;
VarDef
    :
    ID
    {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(nowType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    |
    ID ASSIGN Exp
    {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(nowType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        $$ = new DeclStmt(new Id(se), $3);
        delete []$1;
    }
    ;
ConstDef
    :
    ID
    {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(TypeSystem::getConstTypeOf(nowType), $1, identifiers->getLevel());
        identifiers->install($1, se);
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    |
    ID ASSIGN Exp
    {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(TypeSystem::getConstTypeOf(nowType), $1, identifiers->getLevel());
        identifiers->install($1, se);
        $$ = new DeclStmt(new Id(se), $3);
        delete []$1;
    }
    ;



FuncDef
    :
    Type ID 
    {
        
        identifiers = new SymbolTable(identifiers);
    }
    LPAREN FuncParam RPAREN
    Stmt
    {
        Type *funcType;
        funcType = new FunctionType($1, $5->getTypes()); // FunctionType(Type* returnType, std::vector<Type*> paramsType)
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        globals->install($2, se); // 函数定义时，将函数名加入全局符号表
        

        $$ = new FunctionDef(se, $5, $7);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    ;
FuncParam
    :
    %empty {$$ = new FuncParams();} // no parameters
    |
    Type ID {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        DeclStmt* decl = new DeclStmt(new Id(se));
        $$ = new FuncParams();
        $$->append($1, decl);
        delete []$2;
    }
    |
    FuncParam COMMA Type ID {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($3, $4, identifiers->getLevel());
        identifiers->install($4, se);
        DeclStmt* decl = new DeclStmt(new Id(se));
        $$->append($3, decl);
        delete []$4;
    }
    ;
%%

int yyerror(char const* message)
{
    std::cerr<<message<<"at line "<<yyget_lineno()<<std::endl;
    return -1;
}
