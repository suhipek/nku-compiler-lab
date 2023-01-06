#ifndef __UNIT_H__
#define __UNIT_H__

#include <vector>
#include <set>
#include "Function.h"
#include "AsmBuilder.h"
#include "SymbolTable.h"

class Unit
{
    typedef std::vector<Function *>::iterator iterator;
    typedef std::vector<Function *>::reverse_iterator reverse_iterator;

private:
    std::vector<Function *> func_list;
    IdentifierSymbolEntry* decl_list[1000] = {nullptr}; // 这鬼地方用不了第二个vector...
    int decl_num = 0;
    std::string init_values[1000] = {"0"};
    // std::vector<IdentifierSymbolEntry *> decl_list;
    
public:
    Unit() = default;
    ~Unit() ;
    void insertFunc(Function *);
    void insertDecl(IdentifierSymbolEntry *se, std::string init_val = "0");
    void removeFunc(Function *);
    void output() const;
    iterator begin() { return func_list.begin(); };
    iterator end() { return func_list.end(); };
    reverse_iterator rbegin() { return func_list.rbegin(); };
    reverse_iterator rend() { return func_list.rend(); };
    void genMachineCode(MachineUnit* munit);
};

#endif