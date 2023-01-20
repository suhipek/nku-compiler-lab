#include "Function.h"
#include "Unit.h"
#include "Type.h"
#include <list>

extern FILE *yyout;

Function::Function(Unit *u, SymbolEntry *s, std::vector<Operand *> params_list)
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
    FunctionType *funcType = dynamic_cast<FunctionType *>(sym_ptr->getType());
    Type *retType = funcType->getRetType();
    std::string params_str;

    for (auto &param : params_list)
    {
        params_str += param->getType()->toStr() + " " + param->toStr();
        if (param != params_list.back())
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

std::vector<std::vector<int>> Function::getBlockMap()
{
    int len = block_list.size();
    std::vector<std::vector<int>> m(len, std::vector<int>(len, 0));
    for (int i = 0; i < len; i++)
    {
        auto iter = block_list[i]->succ_begin();
        auto end = block_list[i]->succ_end();
        while (iter != end)
        {
            int j = find(block_list.begin(), block_list.end(), *iter) -
                    block_list.begin();
            m[i][j] = 1;
            iter++;
        }
    }
    return m;
}

int TreeNode::total_num = 0;

void Function::computeDFSTree()
{
    TreeNode::total_num = 0;
    int len = block_list.size();
    preOrder2DFS.resize(len);
    bool *visited = new bool[len]{};
    DFSTreeRoot = new TreeNode(entry);
    preOrder2DFS[DFSTreeRoot->num] = DFSTreeRoot;
    search(DFSTreeRoot, visited);
    delete[] visited;
}

void Function::search(TreeNode *node, bool *visited)
{
    int n = getIndex(node->block);
    visited[n] = true;
    auto block = block_list[n];
    for (auto it = block->succ_begin(); it != block->succ_end(); it++)
    {
        int idx = getIndex(*it);
        if (!visited[idx])
        {
            TreeNode *child = new TreeNode(*it);
            preOrder2DFS[child->num] = child;
            child->parent = node;
            node->addChild(child);
            search(child, visited);
        }
    }
}

int Function::eval(int v, int *ancestors)
{
    int a = ancestors[v];
    while (a != -1 && ancestors[a] != -1)
    {
        if (sdoms[v] > sdoms[a])
            v = a;
        a = ancestors[a];
    }
    return v;
}

void Function::computeSdom()
{
    int len = block_list.size();
    sdoms.resize(len);
    int *ancestors = new int[len];
    for (int i = 0; i < len; i++)
    {
        sdoms[i] = i;
        ancestors[i] = -1;
    }
    for (auto it = preOrder2DFS.rbegin(); (*it)->block != entry; it++)
    {
        auto block = (*it)->block;
        int s = block->order;
        for (auto it1 = block->pred_begin(); it1 != block->pred_end(); it1++)
        {
            int z = eval((*it1)->order, ancestors);
            if (sdoms[z] < sdoms[s])
                sdoms[s] = sdoms[z];
        }
        ancestors[s] = (*it)->parent->num;
    }
    delete[] ancestors;
}

int Function::LCA(int i, int j)
{
    TreeNode *n1 = preOrder2dom[i];
    TreeNode *n2 = preOrder2dom[j];
    int h1 = n1->getHeight();
    int h2 = n2->getHeight();
    if (h1 > h2)
    {
        std::swap(h1, h2);
        std::swap(n1, n2);
    }
    int h = h2 - h1;
    for (int i = 0; i < h; i++)
        n2 = n2->parent;
    while (n1 && n2)
    {
        if (n1 == n2)
            return n1->num;
        n1 = n1->parent;
        n2 = n2->parent;
    }
    return -1;
}

void Function::computeIdom()
{
    int len = block_list.size();
    idoms.resize(len);
    domTreeRoot = new TreeNode(entry, 0);
    preOrder2dom.resize(len);
    preOrder2dom[entry->order] = domTreeRoot;
    idoms[entry->order] = 0;
    for (auto it = preOrder2DFS.begin() + 1; it != preOrder2DFS.end(); it++)
    {
        int p = LCA((*it)->parent->num, sdoms[(*it)->num]);
        idoms[(*it)->num] = p;
        auto parent = preOrder2dom[p];
        TreeNode *node = new TreeNode((*it)->block, 0);
        node->parent = parent;
        parent->addChild(node);
        preOrder2dom[(*it)->num] = node;
    }
}

void Function::computeDomFrontier()
{
    for (auto block : block_list)
    {
        if (block->getNumOfPred() >= 2)
        {
            for (auto it = block->pred_begin(); it != block->pred_end(); it++)
            {
                int runner = (*it)->order;
                while (runner != idoms[block->order])
                {
                    preOrder2DFS[runner]->block->domFrontier.insert(block);
                    runner = idoms[runner];
                }
            }
        }
    }
}