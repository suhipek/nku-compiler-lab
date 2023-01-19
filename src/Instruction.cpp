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

std::vector<Operand *> BinaryInstruction::getUse()
{
    std::vector<Operand *> ret;
    ret.push_back(operands[1]);
    ret.push_back(operands[2]);
    return ret;
}

Operand* BinaryInstruction::getDef()
{
    return operands[0];
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

std::vector<Operand *> CmpInstruction::getUse()
{
    std::vector<Operand *> ret;
    ret.push_back(operands[1]);
    ret.push_back(operands[2]);
    return ret;
}

Operand* CmpInstruction::getDef()
{
    return operands[0];
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

std::vector<Operand *> CondBrInstruction::getUse()
{
    std::vector<Operand *> ret;
    ret.push_back(operands[0]);
    return ret;
}

void CondBrInstruction::output() const
{
    std::string cond, type;
    cond = operands[0]->toStr();
    type = operands[0]->getType()->toStr();
    int true_label = true_branch->getNo();
    int false_label = false_branch->getNo();
    fprintf(yyout, "  br %s %s, label %%B%d, label %%B%d", type.c_str(), cond.c_str(), true_label, false_label);
    if (operands[0]->constInit)
        fprintf(yyout, " ; %d", operands[0]->constValue);
    fprintf(yyout, "\n");
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

std::vector<Operand *> RetInstruction::getUse()
{
    std::vector<Operand *> ret;
    if(!operands.empty())
        ret.push_back(operands[0]);
    return ret;
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

Operand* AllocaInstruction::getDef()
{
    return operands[0];
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

std::vector<Operand *> LoadInstruction::getUse()
{
    std::vector<Operand *> use;
    use.push_back(operands[1]);
    return use;
}

Operand* LoadInstruction::getDef()
{
    return operands[0];
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

std::vector<Operand *> StoreInstruction::getUse()
{
    std::vector<Operand *> use;
    use.push_back(operands[0]);
    use.push_back(operands[1]);
    return use;
}

void StoreInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string dst_type = operands[0]->getType()->toStr();
    std::string src_type = operands[1]->getType()->toStr();

    fprintf(yyout, "  store %s %s, %s* %s, align 4\n", 
        src_type.c_str(), src.c_str(), src_type.c_str(), dst.c_str());
}


CallInstruction::CallInstruction(
    Operand *dst, SymbolEntry *se, std::vector<Operand*> &args, BasicBlock *insert_bb) : Instruction(CALL, insert_bb)
{
    // todo: how to pass args and se as operands
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

std::vector<Operand *> CallInstruction::getUse()
{
    std::vector<Operand *> use;
    for(auto it = operands.begin() + 1; it != operands.end(); ++it)
        use.push_back(*it);
    return use;
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

std::vector<Operand *> SextInstruction::getUse()
{
    std::vector<Operand *> use;
    use.push_back(operands[0]);
    use.push_back(operands[1]);
    return use;
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

GepInstruction::GepInstruction(Operand *dst, Operand *src, std::vector<Operand*> &args, BasicBlock *insert_bb)
    : Instruction(GEP, insert_bb)
{
    operands.push_back(dst);
    operands.push_back(src);
    dst->addUse(this);
    src->addUse(this);
    for(auto it = args.begin(); it != args.end(); ++it)
    {
        operands.push_back(*it);
        (*it)->addUse(this);
    }
}

GepInstruction::~GepInstruction()
{
    operands[0]->removeUse(this);
    operands[1]->removeUse(this);
    for(auto it = operands.begin() + 2; it != operands.end(); ++it)
        (*it)->removeUse(this);
}

void GepInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string arr = operands[1]->toStr();
    std::string dst_type = operands[0]->getType()->toStr();
    std::string arr_type = operands[1]->getType()->toStr();
    std::string ele_type = ((PointerType *)(operands[1]->getType()))->getValueType()->toStr();
    std::string gep_params;
    for(auto it = operands.begin() + 2; it != operands.end(); ++it)
    {
        std::string arg = (*it)->toStr();
        std::string arg_type = (*it)->getType()->toStr();
        gep_params += arg_type + " " + arg;
        if(it != operands.end() - 1)
            gep_params += ", ";
    }

    // %ptr = getelementptr i32, i32* %arr, i32 2, i32 3
    fprintf(yyout, "  %s = getelementptr inbounds %s, %s %s, i32 0, %s\n", 
        dst.c_str(), ele_type.c_str(), arr_type.c_str(), arr.c_str(), gep_params.c_str());
}