#include "Function.h"
#include "Unit.h"
#include "Type.h"
#include <list>

extern FILE* yyout;

Function::Function(Unit *u, SymbolEntry *s, std::vector<Operand*> params_list)
{
    this->params_list = params_list;
    u->insertFunc(this);
    entry = new BasicBlock(this);
    sym_ptr = s;
    parent = u;
}

Function::~Function()
{
    // SegFault :(
    // auto delete_list = block_list;
    // for (auto &i : block_list)
    //     delete i;
    // parent->removeFunc(this);
    // 一个处理程序行数不到一百行的玩具编译器担心内存泄漏干啥
    // 破案了，我连玩具编译器都写不出来，我是five
}

// remove the basicblock bb from its block_list.
void Function::remove(BasicBlock *bb)
{
    block_list.erase(std::find(block_list.begin(), block_list.end(), bb));
}

void Function::output() const
{
    FunctionType* funcType = dynamic_cast<FunctionType*>(sym_ptr->getType());
    Type *retType = funcType->getRetType();
    std::string params_str;

    for(auto &param:params_list)
    {
        params_str += param->getType()->toStr() + " " + param->toStr();
        if(param != params_list.back())
            params_str += ", ";
    }

    fprintf(yyout, "define %s %s(%s) {\n", 
        retType->toStr().c_str(), 
        sym_ptr->toStr().c_str(),
        params_str.c_str());

    std::set<BasicBlock *> v;
    std::list<BasicBlock *> q;
    q.push_back(entry);
    v.insert(entry);
    while (!q.empty())
    {
        auto bb = q.front();
        q.pop_front();
        bb->output();
        for (auto succ = bb->succ_begin(); succ != bb->succ_end(); succ++)
        {
            if (v.find(*succ) == v.end())
            {
                v.insert(*succ);
                q.push_back(*succ);
            }
        }
    }

    // for(auto &bb:block_list)
    //     bb->output();

    fprintf(yyout, "}\n");
}


std::vector<std::vector<int>> Function::getBlockMap() {
    int len = block_list.size();
    std::vector<std::vector<int>> m(len, std::vector<int>(len, 0));
    for (int i = 0; i < len; i++) {
        auto iter = block_list[i]->succ_begin();
        auto end = block_list[i]->succ_end();
        while (iter != end) {
            int j = find(block_list.begin(), block_list.end(), *iter) -
                    block_list.begin();
            m[i][j] = 1;
            iter++;
        }
    }
    return m;
} 