#include "Mem2reg.h"
#include <map>
#include <set>
#include <vector>
#include "BasicBlock.h"
#include "Instruction.h"
#include "Type.h"
using namespace std;

void Mem2reg::pass()
{
    auto iter = unit->begin();
    while (iter != unit->end())
        pass(*iter++);
}

void Mem2reg::pass(Function *function)
{
    checkCondBranch(function); // 清理条件分支
    function->computeDFSTree();
    function->computeSdom();        // 计算严格支配
    function->computeIdom();        // 计算立即支配
    function->computeDomFrontier(); // 计算支配边界
    unit->output();
    insertPhiInstruction(function); // 插入phi指令
    unit->output();
    rename(function); // 重命名
    unit->output();
    cleanAddZeroIns(function); // 清除多余的add指令
}

void Mem2reg::insertPhiInstruction(Function *function)
{
    vector<BinaryInstruction *>().swap(addZeroIns);
    vector<AllocaInstruction *>().swap(allocaIns);
    BasicBlock *entry = function->getEntry();
    for (auto inst = entry->begin(); inst != entry->end(); inst = inst->getNext())
    {
        // 找到所有的alloca指令
        if (inst->getInstType() != Instruction::ALLOCA)
            break;
        auto alloca = (AllocaInstruction *)inst;
        allocaIns.push_back(alloca);
    }
    vector<BasicBlock *> worklist;                   // 工作列表 which blocks have been processed and which need to be processed
    set<BasicBlock *> inWorklist, inserted, assigns; // 已经在工作列表中的块，已经插入phi指令的块，已经赋值的块
    for (auto allocInst : allocaIns)
    {
        // 遍历 Defs(v)
        vector<BasicBlock *>().swap(worklist);
        inWorklist.clear();
        inserted.clear();
        assigns.clear();
        auto block = allocInst->getParent();
        block->remove(allocInst);
        auto operand = allocInst->getDef();
        operand->setDef(nullptr);
        Operand *newOperand = new Operand(new TemporarySymbolEntry(
            ((PointerType *)(operand->getType()))->getValueType(),
            SymbolTable::getLabel()));     // 新的临时变量
        allocInst->replaceDef(newOperand); // 将新的临时变量替换alloca指令的定值
        while (operand->use_begin() != operand->use_end())
        {
            auto use = operand->use_begin();
            if ((*use)->getInstType() == Instruction::STORE)
            {
                if ((*use)->getUse().size() > 1 && newOperand != (*use)->getUse()[1])
                {
                    // 如果是store指令，且不是将新的临时变量赋值给自己
                    // 插入一个add指令，用作赋值
                    auto assignIns = new BinaryInstruction(
                        BinaryInstruction::ADD, newOperand, (*use)->getUse()[1],
                        new Operand(new ConstantSymbolEntry(newOperand->getType(), 0)));
                    addZeroIns.push_back(assignIns);                    // 存一下，以便后面清除
                    (*use)->getParent()->insertBefore(assignIns, *use); // 将add指令插入到store指令之前
                    assigns.insert((*use)->getParent());
                    (*use)->getUse()[1]->removeUse(*use);
                }
            }
            auto dst = (*use)->getDef();
            (*use)->getParent()->remove(*use);
            if (dst && dst != newOperand) // 如果使用者的定值不是新的临时变量
                while (dst->use_begin() != dst->use_end())
                {
                    auto u = *(dst->use_begin());
                    u->replaceUse(dst, newOperand);
                }
            operand->removeUse(*use);
        }
        for (auto block : assigns)
        {
            // 遍历已经赋值的块
            worklist.push_back(block);
            inWorklist.insert(block);
            while (!worklist.empty())
            {
                BasicBlock *n = worklist[0];
                worklist.erase(worklist.begin());
                for (auto m : n->domFrontier)
                {
                    if (inserted.find(m) == inserted.end())
                    {
                        auto phi = new PhiInstruction(newOperand);
                        m->insertFront(phi);
                        inserted.insert(m);
                        if (inWorklist.find(m) == inWorklist.end())
                        {
                            inWorklist.insert(m);
                            worklist.push_back(m);
                        }
                    }
                }
            }
        }
    }
}

void Mem2reg::rename(Function *function)
{
    stacks.clear();
    for (auto i : allocaIns)
    {
        auto operand = i->getDef();
        stacks[operand] = stack<Operand *>();
    }
    rename(function->getEntry());
}

void Mem2reg::rename(BasicBlock *block)
{
    std::map<Operand *, int> counter;
    for (auto inst = block->begin(); inst != block->end(); inst = inst->getNext())
    {
        Operand *def = inst->getDef();
        if (def && stacks.find(def) != stacks.end())
        {
            // 是alloca的def
            counter[def]++;
            Operand *new_ = newName(def);
            inst->replaceDef(new_);
        }
        // 遍历所有指令并替换use
        if (inst->getInstType() != Instruction::PHI)
            for (auto u : inst->getUse())
                if (stacks.find(u) != stacks.end() && !stacks[u].empty())
                    inst->replaceUse(u, stacks[u].top());
    }
    for (auto it = block->succ_begin(); it != block->succ_end(); it++)
    {
        for (auto inst = (*it)->begin(); inst != (*it)->end(); inst = inst->getNext())
        {
            // 替换PHI中的Operand
            if (inst->getInstType() == Instruction::PHI)
            {
                PhiInstruction *phi = (PhiInstruction *)inst;
                Operand *o = phi->getOriginDef();
                if (!stacks[o].empty())
                    phi->addSrc(block, stacks[o].top());
                else
                    phi->addSrc(block, new Operand(new ConstantSymbolEntry(
                                           TypeSystem::intType, 0)));
            }
            else
                break;
        }
    }
    auto func = block->getParent();
    auto node = func->getDomNode(block);
    for (auto child : node->children)
        rename(child->block); // 递归处理后继块
    for (auto it : counter)
        for (int i = 0; i < it.second; i++)
            stacks[it.first].pop();
}

Operand *Mem2reg::newName(Operand *old)
{
    Operand *ret;
    SymbolEntry *old_se = old->getSymEntry();
    if (old_se->isTemporary())
        ret = new Operand(new TemporarySymbolEntry(
            old_se->getType(), SymbolTable::getLabel()));
    else
        ret = new Operand(*old);
    stacks[old].push(ret);
    return ret;
}

void Mem2reg::cleanAddZeroIns(Function *func)
{
    auto type = (FunctionType *)(func->getSymPtr()->getType());
    int paramNo = type->getParamsType().size() - 1;
    int regNum = 4;
    if (paramNo > 3)
        regNum--;
    for (auto i : addZeroIns)
    {
        auto use = i->getUse()[0];
        if (i->getParent()->begin() == i && i->getNext()->isUncond())
            continue;
        if (use->getSymEntry()->isVariable())
        {
            continue;
        }
        auto def = i->getDef();
        auto blocks = func->getBlockList();
        for (auto block : blocks)
        {
            for (auto inst = block->begin(); inst != block->end(); inst = inst->getNext())
            {
                inst->replaceUse(def, use);
            }
        }
        i->getParent()->remove(i);
        use->removeUse(i);
        delete i;
    }
}

void Mem2reg::checkCondBranch(Function *func)
{
    // 检查条件分支是否有重复的
    for (auto block : func->getBlockList())
    {
        auto in = block->rbegin();
        if (in->isCond())
        {
            auto cond = (CondBrInstruction *)in;
            auto trueBlock = cond->getTrueBranch();
            auto falseBlock = cond->getFalseBranch();
            if (trueBlock == falseBlock)
            {
                block->removeSucc(trueBlock);
                trueBlock->removePred(block);
                new UncondBrInstruction(trueBlock, block);
                block->remove(in);
            }
        }
    }
}