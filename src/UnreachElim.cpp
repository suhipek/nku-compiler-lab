#include "UnreachElim.h"
#include <algorithm>
#include <stack>
using namespace std;

extern Unit unit;

void UnreachElim::pass() {
    
    for (auto it = unit->begin(); it != unit->end(); it++) 
    {
        if(debug_on)
            unit->output();
        rmConstBr(*it);
        if(debug_on)
            unit->output();
        rmUnreachBB(*it);
    }
}

void UnreachElim::rmUnreachBB(Function* func) {
    auto reachedList = getReachBlocks(func, 0);
    auto& blockList = func->getBlockList();
    int len = blockList.size();
    bool again = false;
    int i;
    for (i = 1; i < len; i++) 
    {
        if (find(reachedList.begin(), reachedList.end(), i) == reachedList.end()) 
        {
            again = true; // 有需要删除的块
            break;
        }
    }
    if (again) 
    {
        BasicBlock* block = blockList[i];
        for (auto iter = block->pred_begin(); iter != block->pred_end(); iter++)
            (*iter)->removeSucc(block);
        for (auto iter = block->succ_begin(); iter != block->succ_end(); iter++)
            (*iter)->removePred(block);
        blockList.erase(blockList.begin() + i);
        rmUnreachBB(func); // 递归直到没有需要删除的块
    }
}

vector<int> UnreachElim::getReachBlocks(Function* func, int idx) {
    // 遍历流图，找出可达块
    auto bMap = func->getBlockMap();
    int len = bMap.size();
    vector<bool> visited(len, false);
    stack<int> stk;
    stk.push(idx);
    int visiting;
    while (!stk.empty()) 
    {
        visiting = stk.top();
        stk.pop();
        if (!visited[visiting])
            visited[visiting] = true;
        for (int i = 0; i < len; i++)
        {
            if (bMap[visiting][i] && !visited[i])
                stk.push(i);
        }
    }
    vector<int> reached;
    for (int i = 0; i < len; i++)
        if (visited[i] && i != idx)
            reached.push_back(i);
    return reached;
}

void UnreachElim::rmConstBr(Function* func)
{
    // 删除无效while和if语句
    for(auto now_bb: func->getBlockList())
    {
        for(auto inst = now_bb->begin(); inst != now_bb->end(); inst = inst->getNext())
        {
            // 遍历指令，如果指令类型为CondBr，且条件为常数，则删除该指令
            if(inst->getInstType() == Instruction::COND)
            {
                
                BasicBlock *to_bb, *other_bb;
                auto brInst = (CondBrInstruction*)inst;
                if(!brInst->isConstCond())
                    continue;
                int val = brInst->getConstCond();
                if(val)
                {
                    to_bb = brInst->getTrueBranch();
                    other_bb = brInst->getFalseBranch();
                }
                else
                {
                    to_bb = brInst->getFalseBranch();
                    other_bb = brInst->getTrueBranch();
                }
                new UncondBrInstruction(to_bb, now_bb);
                now_bb->removeSucc(other_bb);
                other_bb->removePred(now_bb);
                now_bb->remove(inst);
            }
        }
    }
}