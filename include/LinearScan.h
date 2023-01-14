/**
 * linear scan register allocation
 */

#ifndef _LINEARSCAN_H__
#define _LINEARSCAN_H__
#include <set>
#include <map>
#include <vector>
#include <list>

class MachineUnit;
class MachineOperand;
class MachineFunction;


class LinearScan
{
private:
    struct Interval
    {
        int start;
        int end;
        bool spill; // whether this vreg should be spilled to memory
        int disp;   // displacement in stack
        int rreg;   // the real register mapped from virtual register if the vreg is not spilled to memory
        std::set<MachineOperand *> defs;
        std::set<MachineOperand *> uses;
    };
    MachineUnit *unit;
    MachineFunction *func;
    std::vector<int> regs;
    std::map<MachineOperand *, std::set<MachineOperand *>> du_chains;
    std::vector<Interval*> intervals;
    std::vector<Interval*> active;
    static bool compareStart(Interval*a, Interval*b);
    void expireOldIntervals(Interval *interval);
    void spillAtInterval(Interval *interval);
    void makeDuChains();
    void computeLiveIntervals();
    bool linearScanRegisterAllocation();
    void modifyCode();
    void genSpillCode();
public:
    LinearScan(MachineUnit *unit);
    void allocateRegisters();
};

// Question: How long does it take to learn Git?
// Answer: One day. Which day? Every day.
// 我问老师说，我有多久时间学会Git?
// 老师说：只能四天！ 我说:好,春天、夏天、秋天、冬天。
// 老师说：三天。 我说：好，昨天、今天、明天。 
// 老师说：不行，两天。 我说：好，白天、黑天。 
// 老师说：不行，就一天！ 我说：好！ 
// 老师茫然问到：哪一天？ 我说：每一天！！

#endif