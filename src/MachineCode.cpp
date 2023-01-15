#include "MachineCode.h"
#include "Type.h"
extern FILE* yyout;

MachineOperand::MachineOperand(int tp, int val)
{
    this->type = tp;
    if(tp == MachineOperand::IMM)
        this->val = val;
    else 
        this->reg_no = val;
}

MachineOperand::MachineOperand(std::string label)
{
    this->type = MachineOperand::LABEL;
    this->label = label;
}

bool MachineOperand::operator==(const MachineOperand&a) const
{
    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

bool MachineOperand::operator<(const MachineOperand&a) const
{
    if(this->type == a.type)
    {
        if(this->type == IMM)
            return this->val < a.val;
        return this->reg_no < a.reg_no;
    }
    return this->type < a.type;

    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

void MachineOperand::PrintReg()
{
    switch (reg_no)
    {
    case 11:
        fprintf(yyout, "fp");
        break;
    case 13:
        fprintf(yyout, "sp");
        break;
    case 14:
        fprintf(yyout, "lr");
        break;
    case 15:
        fprintf(yyout, "pc");
        break;
    default:
        fprintf(yyout, "r%d", reg_no);
        break;
    }
}

void MachineOperand::output() 
{
    /* HINT：print operand
    * Example:
    * immediate num 1 -> print #1;
    * register 1 -> print r1;
    * lable addr_a -> print addr_a; */
    switch (this->type)
    {
    case IMM:
        fprintf(yyout, "#%d", this->val);
        break;
    case VREG:
        fprintf(yyout, "v%d", this->reg_no);
        break;
    case REG:
        PrintReg();
        break;
    case LABEL:
        if (this->label.substr(0, 2) == ".L")
            fprintf(yyout, "%s", this->label.c_str());
        else if(this->label[0] == '@')
            fprintf(yyout, "%s", this->label.substr(1).c_str());
        else
            fprintf(yyout, "addr_%s", this->label.c_str());
    default:
        break;
    }
}

void MachineInstruction::PrintCond()
{
    // condType { EQ, NE, LT, LE , GT, GE, NONE }
    switch (cond)
    {
    case EQ:
        fprintf(yyout, "eq");
        break;
    case NE:
        fprintf(yyout, "ne");
        break;
    case LT:
        fprintf(yyout, "lt");
        break;
    case LE:
        fprintf(yyout, "le");
        break;
    case GT:
        fprintf(yyout, "gt");
        break;
    case GE:
        fprintf(yyout, "ge");
        break;
    default:
        break;
    }
}

BinaryMInstruction::BinaryMInstruction(
    MachineBlock* p, int op, 
    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2, 
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::BINARY;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    src2->setParent(this);
}

void BinaryMInstruction::output() 
{
    // Complete other instructions
    // opType { ADD, SUB, MUL, DIV, AND, OR }
    switch (this->op)
    {
    case BinaryMInstruction::ADD:
        fprintf(yyout, "\tadd ");
        break;
    case BinaryMInstruction::SUB:
        fprintf(yyout, "\tsub ");
        break;
    case BinaryMInstruction::MUL:
        fprintf(yyout, "\tmul ");
        break;
    case BinaryMInstruction::DIV:
        fprintf(yyout, "\tdiv ");
        break;
    case BinaryMInstruction::AND:
        fprintf(yyout, "\tand ");
        break;
    case BinaryMInstruction::OR:
        fprintf(yyout, "\torr ");
        break;
    default:
        break;
    }

    this->PrintCond();
    this->def_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[1]->output();
    fprintf(yyout, "\n");
}

LoadMInstruction::LoadMInstruction(MachineBlock* p,
    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2,
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::LOAD;
    this->op = -1;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    if (src2)
        this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    if (src2)
        src2->setParent(this);
}

void LoadMInstruction::output()
{
    fprintf(yyout, "\tldr ");
    this->def_list[0]->output();
    fprintf(yyout, ", ");

    // Load immediate num, eg: ldr r1, =8
    if(this->use_list[0]->isImm())
    {
        fprintf(yyout, "=%d\n", this->use_list[0]->getVal());
        return;
    }

    // Load address
    if(this->use_list[0]->isReg()||this->use_list[0]->isVReg())
        fprintf(yyout, "[");

    this->use_list[0]->output();
    if( this->use_list.size() > 1 )
    {
        fprintf(yyout, ", ");
        this->use_list[1]->output();
    }

    if(this->use_list[0]->isReg()||this->use_list[0]->isVReg())
        fprintf(yyout, "]");
    fprintf(yyout, "\n");
}

StoreMInstruction::StoreMInstruction(MachineBlock* p,
    MachineOperand* src1, MachineOperand* src2, MachineOperand* src3, 
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::STORE;
    this->op = -1;
    this->cond = cond;
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    if (src3)
        this->use_list.push_back(src3);
    src1->setParent(this);
    src2->setParent(this);
    if (src3)
        src3->setParent(this);
}

void StoreMInstruction::output()
{
    fprintf(yyout, "\tstr ");
    this->use_list[0]->output();
    fprintf(yyout, ", ");

    // Store address
    if(this->use_list[1]->isReg()||this->use_list[1]->isVReg())
        fprintf(yyout, "[");

    this->use_list[1]->output();
    if( this->use_list.size() > 2 )
    {
        fprintf(yyout, ", ");
        this->use_list[2]->output();
    }

    if(this->use_list[1]->isReg()||this->use_list[1]->isVReg())
        fprintf(yyout, "]");
    fprintf(yyout, "\n");
}

MovMInstruction::MovMInstruction(MachineBlock* p, int op, 
    MachineOperand* dst, MachineOperand* src,
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::MOV;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src);
    dst->setParent(this);
    src->setParent(this);
}

void MovMInstruction::output() 
{
    fprintf(yyout, "\tmov");
    this->PrintCond();
    fprintf(yyout, " ");
    this->def_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[0]->output();
    fprintf(yyout, "\n");
}

BranchMInstruction::BranchMInstruction(MachineBlock* p, int op, 
    MachineOperand* dst, 
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::BRANCH;
    this->op = op;
    this->cond = cond;
    this->use_list.push_back(dst);
    dst->setParent(this);
}

void BranchMInstruction::output()
{
    // opType { B, BL, BX };
    switch(this->op)
    {
    case B:
        fprintf(yyout, "\tb");
        break;
    case BL:
        fprintf(yyout, "\tbl");
        break;
    case BX:
        fprintf(yyout, "\tbx");
        break;
    }

    PrintCond();
    fprintf(yyout, " ");
    this->use_list[0]->output();
    fprintf(yyout, "\n");
}

CmpMInstruction::CmpMInstruction(MachineBlock* p, 
    MachineOperand* src1, MachineOperand* src2, 
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::CMP;
    this->op = -1;
    this->cond = cond;
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    src1->setParent(this);
    src2->setParent(this);
    p->setLastCond(cond);
}

void CmpMInstruction::output()
{
    // Jsut for reg alloca test
    // delete it after test
    fprintf(yyout, "\tcmp ");
    this->use_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[1]->output();
    fprintf(yyout, "\n");
}

StackMInstrcuton::StackMInstrcuton(MachineBlock* p, int op, 
    MachineOperand* src,
    int cond)
{
    // TODO：push和pop指令可有多个操作数 push {r1, r2}
    this->parent = p;
    this->type = MachineInstruction::STACK;
    this->op = op;
    this->cond = cond;
    this->use_list.push_back(src);
    src->setParent(this);
}

StackMInstrcuton::StackMInstrcuton(MachineBlock* p, int op, 
                std::vector<MachineOperand*> src,
                int cond)
{
    this->parent = p;
    this->type = MachineInstruction::STACK;
    this->op = op;
    this->cond = cond;
    for(auto iter : src)
    {
        this->use_list.push_back(iter);
        iter->setParent(this);
    }
}

void StackMInstrcuton::output()
{
    // opType { PUSH, POP };
    switch(this->op)
    {
    case PUSH:
        fprintf(yyout, "\tpush ");
        break;
    case POP:
        fprintf(yyout, "\tpop ");
        break;
    }

    // this->use_list[0]->output();
    if(this->use_list.size() > 1)
        fprintf(yyout, "{");
    for(auto iter = this->use_list.begin(); iter != this->use_list.end(); iter++)
    {
        (*iter)->output();
        if(std::next(iter) != this->use_list.end()) 
            fprintf(yyout, ", ");
    }
    if(this->use_list.size() > 1)
        fprintf(yyout, "}");

    fprintf(yyout, "\n");
}

MachineFunction::MachineFunction(MachineUnit* p, SymbolEntry* sym_ptr) 
{ 
    this->parent = p; 
    this->sym_ptr = sym_ptr; 
    this->stack_size = 0;
};

void MachineBlock::output()
{
    fprintf(yyout, ".L%d:\n", this->no);
    for(auto iter : inst_list)
    {  
        MachineInstruction *iter_br = dynamic_cast<BranchMInstruction*>(iter);
        if(iter_br && iter_br->getOp() == BranchMInstruction::BX)
        {
            MachineInstruction* cur_inst = 
                new StackMInstrcuton(nullptr, StackMInstrcuton::POP, 
                    this->parent->getSavedRegs());
            cur_inst->output();
        }
        iter->output();
    }
}

std::vector<MachineOperand *> MachineFunction::getSavedRegs()
{
    auto fp = new MachineOperand(MachineOperand::REG, 11);
    // auto sp = new MachineOperand(MachineOperand::REG, 13);
    auto lr = new MachineOperand(MachineOperand::REG, 14);
    std::vector<MachineOperand *> saved_regs_vec;
    for(auto &iter : saved_regs)
    {
        auto reg = new MachineOperand(MachineOperand::REG, iter);
        saved_regs_vec.push_back(reg);
    }
    saved_regs_vec.push_back(fp);
    saved_regs_vec.push_back(lr);
    return saved_regs_vec;
}

void MachineFunction::output()
{
    const char *func_name = this->sym_ptr->toStr().c_str() + 1;
    fprintf(yyout, "\t.global %s\n", func_name);
    fprintf(yyout, "\t.type %s , %%function\n", func_name);
    fprintf(yyout, "%s:\n", func_name);
    // TODO
    /* Hint:
    *  1. Save fp
    *  2. fp = sp
    *  3. Save callee saved register
    *  4. Allocate stack space for local variable */
    auto fp = new MachineOperand(MachineOperand::REG, 11);
    auto sp = new MachineOperand(MachineOperand::REG, 13);
    // auto lr = new MachineOperand(MachineOperand::REG, 14);


    // save regs
    MachineInstruction* cur_inst = new StackMInstrcuton(nullptr, StackMInstrcuton::PUSH, getSavedRegs());
    cur_inst->output();

    // fp = sp
    cur_inst = new MovMInstruction(nullptr, MovMInstruction::MOV, fp, sp);
    cur_inst->output();

    // allocate stack space
    int size = this->stack_size;
    auto size_op = new MachineOperand(MachineOperand::IMM, size);
    if (size < -255 || size > 255) {
        auto r4 = new MachineOperand(MachineOperand::REG, 4);
        cur_inst = new LoadMInstruction(nullptr, r4, size_op);
        cur_inst->output();
        size_op = r4;
    } 
    cur_inst = new BinaryMInstruction(nullptr, BinaryMInstruction::SUB, sp, sp, size_op);
    cur_inst->output();
    // Traverse all the block in block_list to print assembly code.
    for(auto iter : block_list)
        iter->output();
}

void MachineUnit::PrintGlobalDecl()
{
    // TODO:
    // You need to print global variable/const declarition code;

    if (!global_list.empty()) {
        fprintf(yyout, "\t.data\n");
    }

    for(auto global_decl: global_list)
    {
        IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)global_decl;
        fprintf(yyout, "\t.global %s\n", se->toStr().c_str());
        fprintf(yyout, "\t.align 4\n");
        fprintf(yyout, "\t.size %s, %d\n", se->toStr().c_str(), se->getType()->getSize() / 8);
        fprintf(yyout, "%s:\n", se->toStr().c_str());
        fprintf(yyout, "\t.word %d\n", 0); // TODO: init value and array, wait for merge
    }

}

void MachineUnit::output()
{
    // TODO
    /* Hint:
    * 1. You need to print global variable/const declarition code;
    * 2. Traverse all the function in func_list to print assembly code;
    * 3. Don't forget print bridge label at the end of assembly code!! */
    fprintf(yyout, "\t.arch armv8-a\n");
    fprintf(yyout, "\t.arch_extension crc\n");
    fprintf(yyout, "\t.arm\n");
    PrintGlobalDecl();
    fprintf(yyout, "\t.text\n");
    for(auto iter : func_list)
        iter->output();
    for (auto iter = global_list.begin(); iter != global_list.end(); iter++)
    {
        IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)*iter;
        fprintf(yyout, "addr_%s%d:\n", se->toStr().c_str(), (int)(iter - global_list.begin()));
        fprintf(yyout, "\t.word %s\n", se->toStr().c_str());
    }
}

void MachineInstruction::insertBefore(MachineInstruction* inst)
{
    auto& instructions = parent->getInsts();
    auto it = std::find(instructions.begin(), instructions.end(), this);
    instructions.insert(it, inst);
}

void MachineInstruction::insertAfter(MachineInstruction* inst)
{
    auto& instructions = parent->getInsts();
    auto it = std::find(instructions.begin(), instructions.end(), this);
    instructions.insert(++it, inst);
}

// 真心累了