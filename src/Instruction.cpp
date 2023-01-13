#include "Instruction.h"
#include "BasicBlock.h"
#include <iostream>
#include "Function.h"
#include "Type.h"
extern FILE* yyout;

Instruction::Instruction(unsigned instType, BasicBlock *insert_bb)
{
    prev = next = this;
    opcode = -1;
    this->instType = instType;
    if (insert_bb != nullptr)
    {
        insert_bb->insertBack(this);
        parent = insert_bb;
    }
}

Instruction::~Instruction()
{
    parent->remove(this);
}

BasicBlock *Instruction::getParent()
{
    return parent;
}

void Instruction::setParent(BasicBlock *bb)
{
    parent = bb;
}

void Instruction::setNext(Instruction *inst)
{
    next = inst;
}

void Instruction::setPrev(Instruction *inst)
{
    prev = inst;
}

Instruction *Instruction::getNext()
{
    return next;
}

Instruction *Instruction::getPrev()
{
    return prev;
}

BinaryInstruction::BinaryInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb) : Instruction(BINARY, insert_bb)
{
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

BinaryInstruction::~BinaryInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void BinaryInstruction::output() const
{
    std::string s1, s2, s3, op, type;
    s1 = operands[0]->toStr();
    s2 = operands[1]->toStr();
    s3 = operands[2]->toStr();
    type = operands[0]->getType()->toStr();
    switch (opcode)
    {
    case ADD:
        op = "add";
        break;
    case SUB:
        op = "sub";
        break;
    case MUL:
        op = "mul";
        break;
    case DIV:
        op = "sdiv";
        break;
    case MOD:
        op = "srem";
        break;
    case USUB:
        op = "sub nsw";
        break;
    default:
        break;
    }
    fprintf(yyout, "  %s = %s %s %s, %s\n", s1.c_str(), op.c_str(), type.c_str(), s2.c_str(), s3.c_str());
}

CmpInstruction::CmpInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb): Instruction(CMP, insert_bb){
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

CmpInstruction::~CmpInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void CmpInstruction::output() const
{
    std::string s1, s2, s3, op, type;
    s1 = operands[0]->toStr();
    s2 = operands[1]->toStr();
    s3 = operands[2]->toStr();
    type = operands[1]->getType()->toStr();
    switch (opcode)
    {
    case E:
        op = "eq";
        break;
    case NE:
        op = "ne";
        break;
    case L:
        op = "slt";
        break;
    case LE:
        op = "sle";
        break;
    case G:
        op = "sgt";
        break;
    case GE:
        op = "sge";
        break;
    default:
        op = "";
        break;
    }

    fprintf(yyout, "  %s = icmp %s %s %s, %s\n", s1.c_str(), op.c_str(), type.c_str(), s2.c_str(), s3.c_str());
}

UncondBrInstruction::UncondBrInstruction(BasicBlock *to, BasicBlock *insert_bb) : Instruction(UNCOND, insert_bb)
{
    branch = to;
}

void UncondBrInstruction::output() const
{
    fprintf(yyout, "  br label %%B%d\n", branch->getNo());
}

void UncondBrInstruction::setBranch(BasicBlock *bb)
{
    branch = bb;
}

BasicBlock *UncondBrInstruction::getBranch()
{
    return branch;
}

CondBrInstruction::CondBrInstruction(BasicBlock*true_branch, BasicBlock*false_branch, Operand *cond, BasicBlock *insert_bb) : Instruction(COND, insert_bb){
    this->true_branch = true_branch;
    this->false_branch = false_branch;
    cond->addUse(this);
    operands.push_back(cond);
}

CondBrInstruction::~CondBrInstruction()
{
    operands[0]->removeUse(this);
}

void CondBrInstruction::output() const
{
    std::string cond, type;
    cond = operands[0]->toStr();
    type = operands[0]->getType()->toStr();
    int true_label = true_branch->getNo();
    int false_label = false_branch->getNo();
    fprintf(yyout, "  br %s %s, label %%B%d, label %%B%d\n", type.c_str(), cond.c_str(), true_label, false_label);
}

void CondBrInstruction::setFalseBranch(BasicBlock *bb)
{
    false_branch = bb;
}

BasicBlock *CondBrInstruction::getFalseBranch()
{
    return false_branch;
}

void CondBrInstruction::setTrueBranch(BasicBlock *bb)
{
    true_branch = bb;
}

BasicBlock *CondBrInstruction::getTrueBranch()
{
    return true_branch;
}

RetInstruction::RetInstruction(Operand *src, BasicBlock *insert_bb) : Instruction(RET, insert_bb)
{
    if(src != nullptr)
    {
        operands.push_back(src);
        src->addUse(this);
    }
}

RetInstruction::~RetInstruction()
{
    if(!operands.empty())
        operands[0]->removeUse(this);
}

void RetInstruction::output() const
{
    if(operands.empty())
    {
        fprintf(yyout, "  ret void\n");
    }
    else
    {
        std::string ret, type;
        ret = operands[0]->toStr();
        type = operands[0]->getType()->toStr();
        fprintf(yyout, "  ret %s %s\n", type.c_str(), ret.c_str());
    }
}

AllocaInstruction::AllocaInstruction(Operand *dst, SymbolEntry *se, BasicBlock *insert_bb) : Instruction(ALLOCA, insert_bb)
{
    operands.push_back(dst);
    dst->setDef(this);
    this->se = se;
}

AllocaInstruction::~AllocaInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
}

void AllocaInstruction::output() const
{
    std::string dst, type;
    dst = operands[0]->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "  %s = alloca %s, align 4\n", dst.c_str(), type.c_str());
}

LoadInstruction::LoadInstruction(Operand *dst, Operand *src_addr, BasicBlock *insert_bb) : Instruction(LOAD, insert_bb)
{
    operands.push_back(dst);
    operands.push_back(src_addr);
    dst->setDef(this);
    src_addr->addUse(this);
}

LoadInstruction::~LoadInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}

void LoadInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string src_type;
    std::string dst_type;
    dst_type = operands[0]->getType()->toStr();
    src_type = operands[1]->getType()->toStr();
    fprintf(yyout, "  %s = load %s, %s %s, align 4\n", dst.c_str(), dst_type.c_str(), src_type.c_str(), src.c_str());
}

StoreInstruction::StoreInstruction(Operand *dst_addr, Operand *src, BasicBlock *insert_bb) : Instruction(STORE, insert_bb)
{
    operands.push_back(dst_addr);
    operands.push_back(src);
    dst_addr->addUse(this);
    src->addUse(this);
}

StoreInstruction::~StoreInstruction()
{
    operands[0]->removeUse(this);
    operands[1]->removeUse(this);
}

void StoreInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string dst_type = operands[0]->getType()->toStr();
    std::string src_type = operands[1]->getType()->toStr();

    fprintf(yyout, "  store %s %s, %s %s, align 4\n", src_type.c_str(), src.c_str(), dst_type.c_str(), dst.c_str());
}

MachineOperand* Instruction::genMachineOperand(Operand* ope)
{
    auto se = ope->getEntry();
    MachineOperand* mope = nullptr;
    if(se->isConstant())
        mope = new MachineOperand(MachineOperand::IMM, dynamic_cast<ConstantSymbolEntry*>(se)->getValue());
    else if(se->isTemporary())
        mope = new MachineOperand(MachineOperand::VREG, dynamic_cast<TemporarySymbolEntry*>(se)->getLabel());
    else if(se->isVariable())
    {
        auto id_se = dynamic_cast<IdentifierSymbolEntry*>(se);
        if(id_se->isGlobal())
            mope = new MachineOperand(id_se->toStr().c_str());
        else
            exit(0);
    }
    return mope;
}

MachineOperand* Instruction::genMachineReg(int reg) 
{
    return new MachineOperand(MachineOperand::REG, reg);
}

MachineOperand* Instruction::genMachineVReg() 
{
    return new MachineOperand(MachineOperand::VREG, SymbolTable::getLabel());
}

MachineOperand* Instruction::genMachineImm(int val) 
{
    return new MachineOperand(MachineOperand::IMM, val);
}

MachineOperand* Instruction::genMachineLabel(int block_no)
{
    std::ostringstream buf;
    buf << ".L" << block_no;
    std::string label = buf.str();
    return new MachineOperand(label);
}

void AllocaInstruction::genMachineCode(AsmBuilder* builder)
{
    /* HINT:
    * Allocate stack space for local variabel
    * Store frame offset in symbol entry */
    auto cur_func = builder->getFunction();
    int offset = cur_func->AllocSpace(4);
    dynamic_cast<TemporarySymbolEntry*>(operands[0]->getEntry())->setOffset(-offset);
}

void LoadInstruction::genMachineCode(AsmBuilder* builder)
{
    auto cur_block = builder->getBlock();
    MachineInstruction* cur_inst = nullptr;
    // Load global operand
    if(operands[1]->getEntry()->isVariable()
        && dynamic_cast<IdentifierSymbolEntry*>(operands[1]->getEntry())->isGlobal())
    {
        auto dst = genMachineOperand(operands[0]);
        auto internal_reg1 = genMachineVReg();
        auto internal_reg2 = new MachineOperand(*internal_reg1);
        auto src = genMachineOperand(operands[1]);
        // example: load r0, addr_a
        cur_inst = new LoadMInstruction(cur_block, internal_reg1, src);
        cur_block->InsertInst(cur_inst);
        // example: load r1, [r0]
        cur_inst = new LoadMInstruction(cur_block, dst, internal_reg2);
        cur_block->InsertInst(cur_inst);
    }
    // Load local operand
    else if(operands[1]->getEntry()->isTemporary()
            && operands[1]->getDef()
            && operands[1]->getDef()->isAlloc())
    {
        // example: load r1, [r0, #4]
        auto dst = genMachineOperand(operands[0]);
        auto src1 = genMachineReg(11);
        auto src2 = genMachineImm(dynamic_cast<TemporarySymbolEntry*>(operands[1]->getEntry())->getOffset());
        cur_inst = new LoadMInstruction(cur_block, dst, src1, src2);
        cur_block->InsertInst(cur_inst);
    }
    // Load operand from temporary variable
    else
    {
        // example: load r1, [r0]
        auto dst = genMachineOperand(operands[0]);
        auto src = genMachineOperand(operands[1]);
        cur_inst = new LoadMInstruction(cur_block, dst, src);
        cur_block->InsertInst(cur_inst);
    }
}

void StoreInstruction::genMachineCode(AsmBuilder* builder)
{
    auto cur_block = builder->getBlock();
    MachineInstruction* cur_inst = nullptr;

    // Store global operand
    if(operands[0]->getEntry()->isVariable()
        && dynamic_cast<IdentifierSymbolEntry*>(operands[0]->getEntry())->isGlobal())
    {
        auto dst = genMachineOperand(operands[0]);
        auto internal_reg1 = genMachineVReg();
        auto internal_reg2 = new MachineOperand(*internal_reg1);
        auto src = genMachineOperand(operands[1]);
        // example: load r0, addr_a
        cur_inst = new LoadMInstruction(cur_block, internal_reg1, dst);
        cur_block->InsertInst(cur_inst);
        // example: store r1, [r0]
        cur_inst = new StoreMInstruction(cur_block, src, internal_reg2);
        cur_block->InsertInst(cur_inst);
    }

    // Store local operand
    else if(operands[0]->getEntry()->isTemporary()
            && operands[0]->getDef()
            && operands[0]->getDef()->isAlloc())
    {
        // example: store r1, [r0, #4]
        auto dst = genMachineOperand(operands[0]);
        auto src = genMachineOperand(operands[1]);
        auto offset = genMachineImm(dynamic_cast<TemporarySymbolEntry*>(operands[0]->getEntry())->getOffset());
        // TODO：此处offset最大为255，如果超出需要临时寄存器转换
        cur_inst = new StoreMInstruction(cur_block, dst, src, offset);
        cur_block->InsertInst(cur_inst);
    }

    // Store operand to temporary variable
    else
    {
        // example: store r1, [r0]
        auto dst = genMachineOperand(operands[0]);
        auto src = genMachineOperand(operands[1]);
        cur_inst = new StoreMInstruction(cur_block, dst, src);
        cur_block->InsertInst(cur_inst);
    }
}

void BinaryInstruction::genMachineCode(AsmBuilder* builder)
{
    // complete other instructions
    auto cur_block = builder->getBlock();
    auto dst = genMachineOperand(operands[0]);
    auto src1 = genMachineOperand(operands[1]);
    auto src2 = genMachineOperand(operands[2]);
    /* HINT:
    * The source operands of ADD instruction in ir code both can be immediate num.
    * However, it's not allowed in assembly code.
    * So you need to insert LOAD/MOV instrucrion to load immediate num into register.
    * As to other instructions, such as MUL, CMP, you need to deal with this situation, too.*/
    MachineInstruction* cur_inst = nullptr;
    if(src1->isImm())
    {
        auto internal_reg = genMachineVReg();
        cur_inst = new LoadMInstruction(cur_block, internal_reg, src1);
        cur_block->InsertInst(cur_inst);
        src1 = new MachineOperand(*internal_reg);
    }
    //ADD, SUB, MUL, DIV, AND, OR, MOD
    switch (opcode)
    {
    case ADD:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::ADD, dst, src1, src2);
        break;
    case SUB:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::SUB, dst, src1, src2);
        break;
    case MUL:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::MUL, dst, src1, src2);
        break;
    case DIV:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::DIV, dst, src1, src2);
        break;
    case AND:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::AND, dst, src1, src2);
        break;
    case OR:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::OR, dst, src1, src2);
        break;
    case MOD:
        // ARM汇编不支持取模，只能先整除再减去
        // dst = src1 / src2
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::DIV, dst, src1, src2);
        cur_block->InsertInst(cur_inst);
        // dst = src1 - dst * src2
        MachineOperand* internal_reg = new MachineOperand(*dst);
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::MUL, internal_reg, dst, src2);
        cur_block->InsertInst(cur_inst);
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::SUB, dst, src1, internal_reg);
    default:
        break;
    }
    cur_block->InsertInst(cur_inst);
}

void CmpInstruction::genMachineCode(AsmBuilder* builder)
{
    // ARM 中的 CMP 指令执行后，会将 Rn 减去 Operand2 的结果丢弃，并将结果的相关信息保存在 CPSR 的 N, Z, C 和 V 标志位中。
    // N 标志位记录结果是否为负数，Z 标志位记录结果是否为零，C 标志位记录结果是否有进位，V 标志位记录结果是否溢出。
    // 这些标志位可以用于后续判断语句中,例如：

    // BEQ label（Z = 1, Equal）
    // BNE label（Z = 0, Not equal）
    // BGT label（Z = 0 and N = V，Greater than）
    // BLT label（Z = 1 or N ≠ V，Less than）
    // BGE label（N = V，Greater than or equal）
    // BLE label（N ≠ V，Less than or equal）

    // 如何进行分支的翻译呢？
    auto cur_block = builder->getBlock();
    auto dst = genMachineOperand(operands[0]);
    auto src1 = genMachineOperand(operands[1]);
    auto src2 = genMachineOperand(operands[2]);
    MachineInstruction* cur_inst = nullptr;
    if(src1->isImm())
    {
        auto internal_reg = genMachineVReg();
        cur_inst = new LoadMInstruction(cur_block, internal_reg, src1);
        cur_block->InsertInst(cur_inst);
        src1 = new MachineOperand(*internal_reg);
    }
    if(src2->isImm())
    {
        auto internal_reg = genMachineVReg();
        cur_inst = new LoadMInstruction(cur_block, internal_reg, src2);
        cur_block->InsertInst(cur_inst);
        src2 = new MachineOperand(*internal_reg);
    }
    cur_inst = new CmpMInstruction(cur_block, src1, src2, opcode);
    cur_block->InsertInst(cur_inst);

    // EQ, NE, LT, LE , GT, GE, NONE
    if(opcode >= CmpMInstruction::LT && opcode <= CmpMInstruction::GE)
    {
        auto trueOpe = genMachineImm(1);
        auto falseOpe = genMachineImm(0);
        // 通过使用movlt、movge等指令进行条件执行
        // 如果结果为真就将dst设置为1，否则设置为0
        // 所以opcode做cond，会被printCond函数输出为movlt等
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst,trueOpe, opcode);
        cur_block->InsertInst(cur_inst);
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst,falseOpe, 7 - opcode);
        cur_block->InsertInst(cur_inst);
    }
}

void UncondBrInstruction::genMachineCode(AsmBuilder* builder)
{
    auto cur_block = builder->getBlock();
    auto dst = genMachineLabel(branch->getNo());
    MachineInstruction* cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::B, dst);
    cur_block->InsertInst(cur_inst);
}

void CondBrInstruction::genMachineCode(AsmBuilder* builder)
{
    auto cur_block = builder->getBlock();

    auto dst = genMachineLabel(true_branch->getNo());
    MachineInstruction* cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::B, dst, 
        cur_block->getLastCond()); // 有条件跳转
    cur_block->InsertInst(cur_inst);

    dst = genMachineLabel(false_branch->getNo());
    cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::B, dst);
    cur_block->InsertInst(cur_inst);
}

void RetInstruction::genMachineCode(AsmBuilder* builder)
{
    /* HINT:
    * 1. Generate mov instruction to save return value in r0
    * 2. Restore callee saved registers and sp, fp
    * 3. Generate bx instruction */
    auto cur_block = builder->getBlock();

    if(operands.size() > 0)
    {
        // 返回值存入r0寄存器
        auto src = genMachineOperand(operands[0]);
        auto cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, genMachineReg(0), // r0
            src);
        cur_block->InsertInst(cur_inst);
    }

    // 恢复sp栈空间大小
    auto cur_func = builder->getFunction();
    auto sp = new MachineOperand(MachineOperand::REG, 13);
    auto size = new MachineOperand(MachineOperand::IMM, cur_func->AllocSpace(0));
    auto cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::ADD, sp, sp, size);
    cur_block->InsertInst(cur_inst);

    // TODO：恢复fp
    // auto fp = new MachineOperand(MachineOperand::REG, 11);

    // 跳转返回
    auto lr = new MachineOperand(MachineOperand::REG, 14);
    cur_block->InsertInst(new BranchMInstruction(cur_block, BranchMInstruction::BX, lr));
}


CallInstruction::CallInstruction(
    Operand *dst, SymbolEntry *se, std::vector<Operand*> &args, BasicBlock *insert_bb) : Instruction(CALL, insert_bb)
{
    operands.push_back(dst);
    dst->addUse(this);
    this->se = se;
    for(auto it = args.begin(); it != args.end(); ++it)
    {
        operands.push_back(*it);
        (*it)->addUse(this);
    }
}

CallInstruction::~CallInstruction()
{
    for(auto it = operands.begin() + 1; it != operands.end(); ++it)
        (*it)->removeUse(this);
}

void CallInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string func_name = se->toStr(); // 记得加上 @
    std::string func_type = se->getType()->toStr();
    std::string func_params;
    // Type *retType = ((FunctionType *)(se->getType()))->getRetType();

    // 遍历转换参数列表
    for(auto it = operands.begin() + 1; it != operands.end(); ++it)
    {
        std::string arg = (*it)->toStr();
        std::string arg_type = (*it)->getType()->toStr();
        func_params += arg_type + " " + arg;
        if(it != operands.end() - 1)
            func_params += ", ";
    }

    Type* retType = ((FunctionType *)(se->getType()))->getRetType();
    if(retType == TypeSystem::voidType)
    {
        fprintf(yyout, "  call %s %s(%s)\n", 
            func_type.c_str(), func_name.c_str(), func_params.c_str());
    }
    else
    {
        fprintf(yyout, "  %s = call %s %s(%s)\n", 
            dst.c_str(), func_type.c_str(), func_name.c_str(), func_params.c_str());
    }
}

SextInstruction::SextInstruction(
    Operand *dst, Operand *src, Type *toType, BasicBlock *insert_bb) : Instruction(SEXT, insert_bb)
{
    operands.push_back(dst);
    operands.push_back(src);
    dst->addUse(this);
    src->addUse(this);
    this->toType = toType;
}

SextInstruction::~SextInstruction()
{
    operands[0]->removeUse(this);
    operands[1]->removeUse(this);
}

void SextInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string dst_type = toType->toStr();
    std::string src_type = operands[1]->getType()->toStr();

    fprintf(yyout, "  %s = sext %s %s to %s\n", 
        dst.c_str(), src_type.c_str(), src.c_str(), dst_type.c_str());
}

void SextInstruction::genMachineCode(AsmBuilder* builder)
{
    auto cur_block = builder->getBlock();
    auto dst = genMachineOperand(operands[0]);
    auto src = genMachineOperand(operands[1]);
    auto cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst, src);
    cur_block->InsertInst(cur_inst);
}

void CallInstruction::genMachineCode(AsmBuilder* builder)
{
    // 在进行函数调用时，对于含参函数，需要使用 R0-R3 寄存器传递参数，如果参数个数大于四个还
    // 需要生成 PUSH 指令来传递参数；之后生成跳转指令来进入 Callee 函数；在此之后，需要进行现场恢
    // 复的工作，如果之前通过压栈的方式传递了参数，需要恢复 SP 寄存器；最后，如果函数执行结果被用
    // 到，还需要保存 R0 寄存器中的返回值。
    auto cur_block = builder->getBlock();
    MachineInstruction *cur_inst;
    // 第一个operand是dst，参数从第二个开始
    // 前四个参数
    for(auto it = operands.begin() + 1; 
        it != operands.end() && it - operands.begin() <= 4; 
        ++it)
    {
        auto op = genMachineReg(it - operands.begin() - 1);
        auto src = genMachineOperand(*it);
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, op, src);
        cur_block->InsertInst(cur_inst);
    }
    // 超出四个参数
    for(auto it = operands.begin() + 5; it != operands.end(); ++it)
    {
        auto src = genMachineOperand(*it);
        cur_inst = new StackMInstrcuton(cur_block, StackMInstrcuton::PUSH, src);
        cur_block->InsertInst(cur_inst);
    }

    // 跳转
    auto label = new MachineOperand(se->toStr());
    cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::BL, label);
    cur_block->InsertInst(cur_inst);

    // 现场恢复
    if(operands.size() > 5)
    {
        auto offset = genMachineImm((operands.size() - 5) * 4);
        auto sp = genMachineReg(13); // SP
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::ADD, sp, sp, offset);
        cur_block->InsertInst(cur_inst);
    }

    // 保存返回值
    Type* retType = ((FunctionType *)(se->getType()))->getRetType();
    if(retType != TypeSystem::voidType)
    {
        auto dst = genMachineOperand(operands[0]);
        auto src = genMachineReg(0); // R0
        cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, dst, src);
        cur_block->InsertInst(cur_inst);
    }
}