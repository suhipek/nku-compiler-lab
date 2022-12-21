#include "Function.h"
#include "Unit.h"
#include "Type.h"
#include "SymbolTable.h"

extern FILE* yyout;

void Unit::insertFunc(Function *f)
{
    func_list.push_back(f);
}

void Unit::insertDecl(IdentifierSymbolEntry *se, std::string init_val)
{
    // fprintf(stderr, "insertDecl: %s, sizeof(ddeclList): %d\n", se->toStr().c_str(), (int)(decl_list.size()));
    init_values[decl_num] = init_val;
    decl_list[decl_num++] = se;
}

void Unit::removeFunc(Function *func)
{
    func_list.erase(std::find(func_list.begin(), func_list.end(), func));
}

void Unit::output() const
{
    // @a = dso_local global i32 3, align 4
    for (int i = 0; i < decl_num; i++)
    {
        IdentifierSymbolEntry *decl = decl_list[i];
        fprintf(yyout, "%s = dso_local global %s %s, align 4\n", 
            decl->toStr().c_str(), 
            decl->getType()->toStr().c_str(),
            init_values[i].c_str());
    }
    for (auto &func : func_list)
        func->output();
}

Unit::~Unit()
{
    for(auto &func:func_list)
        delete func;

}
