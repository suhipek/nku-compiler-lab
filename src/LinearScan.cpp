#include <algorithm>
#include "LinearScan.h"
#include "MachineCode.h"
#include "LiveVariableAnalysis.h"

extern MachineUnit mUnit;

LinearScan::LinearScan(MachineUnit *unit)
{
    this->unit = unit;
    for (int i = 4; i < 11; i++)
        regs.push_back(i);
}

void LinearScan::allocateRegisters()
{
    for (auto &f : unit->getFuncs())
    {
        func = f;
        bool success;
        success = false;
        // mUnit.output();
        while (!success)        // repeat until all vregs can be mapped
        {
            computeLiveIntervals();
            success = linearScanRegisterAllocation();
            if (success)        // all vregs can be mapped to real regs
                modifyCode();
            else                // spill vregs that can't be mapped to real regs
                genSpillCode();
            // mUnit.output(); // for debug
        }
    }
}

void LinearScan::makeDuChains()
{
    LiveVariableAnalysis lva;
    lva.pass(func);
    du_chains.clear();
    int i = 0;
    std::map<MachineOperand, std::set<MachineOperand *>> liveVar;
    for (auto &bb : func->getBlocks())
    {
        liveVar.clear();
        for (auto &t : bb->getLiveOut())
            liveVar[*t].insert(t);
        int no;
        no = i = bb->getInsts().size() + i;
        for (auto inst = bb->getInsts().rbegin(); inst != bb->getInsts().rend(); inst++)
        {
            (*inst)->setNo(no--);
            for (auto &def : (*inst)->getDef())
            {
                if (def->isVReg())
                {
                    auto &uses = liveVar[*def];
                    du_chains[def].insert(uses.begin(), uses.end());
                    auto &kill = lva.getAllUses()[*def];
                    std::set<MachineOperand *> res;
                    set_difference(uses.begin(), uses.end(), kill.begin(), kill.end(), inserter(res, res.end()));
                    liveVar[*def] = res;
                }
            }
            for (auto &use : (*inst)->getUse())
            {
                if (use->isVReg())
                    liveVar[*use].insert(use);
            }
        }
    }
}

void LinearScan::computeLiveIntervals()
{
    makeDuChains();
    intervals.clear();
    for (auto &du_chain : du_chains)
    {
        int t = -1;
        for (auto &use : du_chain.second)
            t = std::max(t, use->getParent()->getNo());
        Interval *interval = new Interval({du_chain.first->getParent()->getNo(), t, false, 0, 0, {du_chain.first}, du_chain.second});
        intervals.push_back(interval);
    }
    for (auto& interval : intervals) {
        auto uses = interval->uses;
        auto begin = interval->start;
        auto end = interval->end;
        for (auto block : func->getBlocks()) {
            auto liveIn = block->getLiveIn();
            auto liveOut = block->getLiveOut();
            bool in = false;
            bool out = false;
            for (auto use : uses)
                if (liveIn.count(use)) {
                    in = true;
                    break;
                }
            for (auto use : uses)
                if (liveOut.count(use)) {
                    out = true;
                    break;
                }
            if (in && out) {
                begin = std::min(begin, (*(block->begin()))->getNo());
                end = std::max(end, (*(block->rbegin()))->getNo());
            } else if (!in && out) {
                for (auto i : block->getInsts())
                    if (i->getDef().size() > 0 &&
                        i->getDef()[0] == *(uses.begin())) {
                        begin = std::min(begin, i->getNo());
                        break;
                    }
                end = std::max(end, (*(block->rbegin()))->getNo());
            } else if (in && !out) {
                begin = std::min(begin, (*(block->begin()))->getNo());
                int temp = 0;
                for (auto use : uses)
                    if (use->getParent()->getParent() == block)
                        temp = std::max(temp, use->getParent()->getNo());
                end = std::max(temp, end);
            }
        }
        interval->start = begin;
        interval->end = end;
    }
    bool change;
    change = true;
    while (change)
    {
        change = false;
        std::vector<Interval *> t(intervals.begin(), intervals.end());
        for (size_t i = 0; i < t.size(); i++)
            for (size_t j = i + 1; j < t.size(); j++)
            {
                Interval *w1 = t[i];
                Interval *w2 = t[j];
                if (**w1->defs.begin() == **w2->defs.begin())
                {
                    std::set<MachineOperand *> temp;
                    set_intersection(w1->uses.begin(), w1->uses.end(), w2->uses.begin(), w2->uses.end(), inserter(temp, temp.end()));
                    if (!temp.empty())
                    {
                        change = true;
                        w1->defs.insert(w2->defs.begin(), w2->defs.end());
                        w1->uses.insert(w2->uses.begin(), w2->uses.end());
                        // w1->start = std::min(w1->start, w2->start);
                        // w1->end = std::max(w1->end, w2->end);
                        auto w1Min = std::min(w1->start, w1->end);
                        auto w1Max = std::max(w1->start, w1->end);
                        auto w2Min = std::min(w2->start, w2->end);
                        auto w2Max = std::max(w2->start, w2->end);
                        w1->start = std::min(w1Min, w2Min);
                        w1->end = std::max(w1Max, w2Max);
                        auto it = std::find(intervals.begin(), intervals.end(), w2);
                        if (it != intervals.end())
                            intervals.erase(it);
                    }
                }
            }
    }
    sort(intervals.begin(), intervals.end(), compareStart);
}

bool LinearScan::linearScanRegisterAllocation()
{
    // Todo
    // 现在开始遍历 intervals 列表进行寄存器分配，这一步需要大家完善 linearScanRegisterAllocation()
    // 函数。对任意一个 unhandled interval 都进行如下的处理：
    // 1. 遍历 active 列表，看该列表中是否存在结束时间早于 unhandled interval 的 interval（即与当前
    // unhandled interval 的活跃区间不冲突），若有，则说明此时为其分配的物理寄存器可以回收，可
    // 以用于后续的分配，需要将其在 active 列表删除；
    // 2. 判断 active 列表中 interval 的数目和可用的物理寄存器数目是否相等，
    // (a) 若相等，则说明当前所有物理寄存器都被占用，需要进行寄存器溢出操作。具体为在 active
    // 列表中最后一个 interval 和当前 unhandled interval 中选择一个 interval 将其溢出到栈中，
    // 选择策略就是看谁的活跃区间结束时间更晚，如果是 unhandled interval 的结束时间更晚，
    // 只需要置位其 spill 标志位即可，如果是 active 列表中的 interval 结束时间更晚，需要置位
    // 其 spill 标志位，并将其占用的寄存器分配给 unhandled interval，再按照 unhandled interval
    // 活跃区间结束位置，将其插入到 active 列表中。
    // (b) 若不相等，则说明当前有可用于分配的物理寄存器，为 unhandled interval 分配物理寄存器
    // 之后，再按照活跃区间结束位置，将其插入到 active 列表中即可。
    bool success = true;
    active.clear();
    regs.clear();
    for(int i = 4; i <= 10; i++)
        regs.push_back(i);
    for(auto &interval:intervals)
    {
        expireOldIntervals(interval); // 回收寄存器（1）
        // 非常奇怪的bug：mul v2, v2, v5会被分配为mul r8, r9, r9
        if(regs.empty())
        {
            // 溢出寄存器（2a）
            spillAtInterval(interval);
            success = false;
        }
        else
        {
            fprintf(stderr, "linearScanRegisterAllocation: assigning register %d to interval %d\n", regs.back(), interval->rreg);
            interval->rreg = regs.back(); // 分配寄存器
            regs.pop_back(); // 从可用寄存器列表中删除
            active.push_back(std::move(interval)); // 将 interval 插入到 active 列表中
            // 按照活跃区间结束位置排序，使用lambda
            sort(active.begin(), active.end(), [](Interval* a, Interval* b) {return a->end < b->end;}); 
        }
        // expireOldIntervals(interval); // 回收寄存器（1）
    }
    return success;
}

void LinearScan::modifyCode()
{
    for (auto &interval : intervals)
    {
        func->addSavedRegs(interval->rreg);
        for (auto def : interval->defs)
            def->setReg(interval->rreg);
        for (auto use : interval->uses)
            use->setReg(interval->rreg);
    }
}

void LinearScan::genSpillCode()
{
    for(auto &interval:intervals)
    {
        if(!interval->spill)
            continue;
        // TODO
        /* HINT:
         * The vreg should be spilled to memory.
         * 1. insert ldr inst before the use of vreg
         * 2. insert str inst after the def of vreg
         */ 
        interval->disp = -func->AllocSpace(4); // 分配栈空间
        auto fp = new MachineOperand(MachineOperand::REG, 11);
        auto offset = new MachineOperand(MachineOperand::IMM, interval->disp);
        MachineInstruction *cur_inst;
        for (auto use: interval->uses)
        {
            // 1. insert ldr inst before the use of vreg
            auto temp = new MachineOperand(*use);
            MachineOperand* operand = nullptr;

            // 立即数超限，插入 ldr vN, offset
            if (interval->disp > 255 || interval->disp < -255) {
                operand = new MachineOperand(MachineOperand::VREG, SymbolTable::getLabel()); 
                cur_inst = new LoadMInstruction(use->getParent()->getParent(), operand, offset);
                use->getParent()->insertBefore(cur_inst);
                offset = new MachineOperand(*operand);
            }

            cur_inst = new LoadMInstruction(use->getParent()->getParent(), temp, fp, offset);
            use->getParent()->insertBefore(cur_inst);
        }

        for (auto def: interval->defs)
        {
            // 2. insert str inst after the def of vreg
            auto temp = new MachineOperand(*def);
            MachineOperand* operand = nullptr;

            // 立即数超限，插入 str vN, offset
            if (interval->disp > 255 || interval->disp < -255) {
                operand = new MachineOperand(MachineOperand::VREG, SymbolTable::getLabel()); 
                cur_inst = new LoadMInstruction(def->getParent()->getParent(), operand, offset);
                def->getParent()->insertAfter(cur_inst);
                offset = new MachineOperand(*operand);
            }

            cur_inst = new StoreMInstruction(def->getParent()->getParent(), temp, fp, offset);
            def->getParent()->insertAfter(cur_inst);
        }
    }
}

void LinearScan::expireOldIntervals(Interval *interval)
{
    for (auto iter = active.begin(); 
        iter != active.end(); ) 
    {
        // if ((*iter)->end >= interval->start)
        // 寄存器分配为什么会出现不正确的回收？
        if ((*iter)->end >= interval->start - 1)
            return; // active按照end升序，头部大于，回收不了
        fprintf(stderr, "expireOldIntervals: recyling register %d\n", (*iter)->rreg);
        regs.push_back((*iter)->rreg);
        iter = active.erase(find(active.begin(), active.end(), *iter));
        sort(regs.begin(), regs.end());
    }
}

void LinearScan::spillAtInterval(Interval *interval)
{
    auto spill = active.back(); // 当前end最大的溢出到栈中
    if (spill->end > interval->end)
    {
        spill->spill = true;
        // fprintf(stderr, "spillAtInterval: assigning register %d to interval %d", regs.back(), interval->rreg);
        interval->rreg = spill->rreg;
        func->addSavedRegs(interval->rreg); // 保存处理寄存器
        active.push_back(std::move(interval)); // 将 interval 插入到 active 列表中
        sort(active.begin(), active.end(), [](Interval* a, Interval* b) {return a->end < b->end;});
    } 
    else 
    {
        interval->spill = true; //unhandle溢出更晚，不用处理active列表
    }
}

bool LinearScan::compareStart(Interval *a, Interval *b)
{
    return a->start < b->start;
}

// Question: What's best version control tool?
// Answer: WeChat