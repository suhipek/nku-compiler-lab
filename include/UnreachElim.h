#ifndef __ELIM_UNREACH_CODE_H
#define __ELIM_UNREACH_CODE_H

#include <vector>
#include "Unit.h"

class UnreachElim {
    Unit* unit;
    bool debug_on;

   public:
    UnreachElim(Unit* unit, bool debug = false) : unit(unit), debug_on(debug){};
    void pass();
    void rmUnreachBB(Function* function);
    void rmConstBr(Function* function);
    std::vector<int> getReachBlocks(Function* func, int idx);
};

#endif