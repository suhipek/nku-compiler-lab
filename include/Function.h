#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <vector>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include "BasicBlock.h"
#include "SymbolTable.h"

class Unit;

class TreeNode
{
public:
    // num only use for dfs tree node
    static int total_num;
    int num;
    BasicBlock *block;
    std::vector<TreeNode *> children;
    TreeNode *parent = nullptr;
    // only use for dfs tree node
    TreeNode(BasicBlock *block) : block(block)
    {
        num = total_num++;
        block->order = num;
    }
    // only use for dom tree node
    TreeNode(BasicBlock *block, int num) : block(block)
    {
        this->num = block->order;
    }
    void addChild(TreeNode *child) { children.push_back(child); }
    // only use for dom tree node
    int getHeight()
    {
        int height = 0;
        TreeNode *temp = this;
        while (temp)
        {
            height++;
            temp = temp->parent;
        }
        return height;
    }
};

class Function
{
    typedef std::vector<BasicBlock *>::iterator iterator;
    typedef std::vector<BasicBlock *>::reverse_iterator reverse_iterator;

private:
    std::vector<BasicBlock *> block_list;
    SymbolEntry *sym_ptr;
    BasicBlock *entry;
    Unit *parent;
    std::vector<Operand *> params_list;
    TreeNode* DFSTreeRoot;
    TreeNode* domTreeRoot;
    // preOrder2DFS order-> dfs tree node
    std::vector<TreeNode*> preOrder2DFS;
    // preOrder2dom order-> dom tree node
    std::vector<TreeNode*> preOrder2dom;
    std::vector<int> sdoms;
    std::vector<int> idoms;

public:
    Function(Unit *, SymbolEntry *, std::vector<Operand *>);
    ~Function();
    void insertBlock(BasicBlock *bb) { block_list.push_back(bb); };
    BasicBlock *getEntry() { return entry; };
    void remove(BasicBlock *bb);
    void output() const;
    std::vector<BasicBlock *> &getBlockList() { return block_list; };
    std::vector<std::vector<int>> getBlockMap();
    iterator begin() { return block_list.begin(); };
    iterator end() { return block_list.end(); };
    reverse_iterator rbegin() { return block_list.rbegin(); };
    reverse_iterator rend() { return block_list.rend(); };
    SymbolEntry *getSymPtr() { return sym_ptr; };

    void computeDFSTree();
    void search(TreeNode *node, bool *visited);
    int getIndex(BasicBlock *block)
    {
        return std::find(block_list.begin(), block_list.end(), block) -
               block_list.begin();
    }
    int eval(int i, int *ancestors);
    void computeSdom();
    int LCA(int i, int j);
    void computeIdom();
    void domTest();
    void computeDomFrontier();
    TreeNode* getDomNode(BasicBlock* bb) { return preOrder2dom[bb->order]; }
};

#endif
