#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "Operand.h"
#include <vector>
#include <map>

class BasicBlock;

class Instruction
{
public:
    Instruction(unsigned instType, BasicBlock *insert_bb = nullptr);
    virtual ~Instruction();
    BasicBlock *getParent();
    bool isUncond() const {return instType == UNCOND;};
    bool isCond() const {return instType == COND;};
    unsigned getOpcode() const {return opcode;};
    unsigned getInstType() const {return instType;};
    void setParent(BasicBlock *);
    void setNext(Instruction *);
    void setPrev(Instruction *);
    Instruction *getNext();
    Instruction *getPrev();
    virtual Operand* getDef(){return nullptr;};
    virtual std::vector<Operand *> getUse(){return std::vector<Operand *>();};
    virtual void replaceUse(Operand* old, Operand* income) {}
    virtual void replaceDef(Operand* income) {}
    virtual void output() const = 0;
    enum {BINARY, COND, UNCOND, RET, LOAD, STORE, CMP, ALLOCA, CALL, SEXT, GEP, PHI};
protected:
    unsigned instType;
    unsigned opcode;
    Instruction *prev;
    Instruction *next;
    BasicBlock *parent;
    std::vector<Operand*> operands;
};

// meaningless instruction, used as the head node of the instruction list.
class DummyInstruction : public Instruction
{
public:
    DummyInstruction() : Instruction(-1, nullptr) {};
    void output() const {};
};

class AllocaInstruction : public Instruction
{
public:
    AllocaInstruction(Operand *dst, SymbolEntry *se, BasicBlock *insert_bb = nullptr);
    ~AllocaInstruction();
    Operand* getDef();
    void replaceDef(Operand* income);
    void output() const;
private:
    SymbolEntry *se;
};

class LoadInstruction : public Instruction
{
public:
    LoadInstruction(Operand *dst, Operand *src_addr, BasicBlock *insert_bb = nullptr);
    ~LoadInstruction();
    std::vector<Operand *> getUse();
    Operand* getDef();
    void replaceUse(Operand* old, Operand* income);
    void replaceDef(Operand* income);
    void output() const;
};

class StoreInstruction : public Instruction
{
public:
    StoreInstruction(Operand *dst_addr, Operand *src, BasicBlock *insert_bb = nullptr);
    ~StoreInstruction();
    std::vector<Operand *> getUse();
    void replaceUse(Operand* old, Operand* income);
    void output() const;
};

class BinaryInstruction : public Instruction
{
public:
    BinaryInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb = nullptr);
    ~BinaryInstruction();
    std::vector<Operand *> getUse();
    Operand* getDef();
    void replaceUse(Operand* old, Operand* income);
    void replaceDef(Operand* income);
    void output() const;
    enum {SUB, ADD, MUL, DIV, MOD, AND, OR, USUB};
};

class CmpInstruction : public Instruction
{
public:
    CmpInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb = nullptr);
    ~CmpInstruction();
    std::vector<Operand *> getUse();
    Operand* getDef();
    void replaceUse(Operand* old, Operand* income);
    void replaceDef(Operand* income);
    void output() const;
    enum {E, NE, L, GE, G, LE};
};

// unconditional branch
class UncondBrInstruction : public Instruction
{
public:
    UncondBrInstruction(BasicBlock*, BasicBlock *insert_bb = nullptr);
    void output() const;
    void setBranch(BasicBlock *);
    BasicBlock *getBranch();
protected:
    BasicBlock *branch;
};

// conditional branch
class CondBrInstruction : public Instruction
{
public:
    CondBrInstruction(BasicBlock*, BasicBlock*, Operand *, BasicBlock *insert_bb = nullptr);
    ~CondBrInstruction();
    std::vector<Operand *> getUse();
    void replaceUse(Operand* old, Operand* income);
    void output() const;
    bool isConstCond() {return operands[0]->constInit;}
    int getConstCond() {return operands[0]->constValue;}
    void setTrueBranch(BasicBlock*);
    BasicBlock* getTrueBranch();
    void setFalseBranch(BasicBlock*);
    BasicBlock* getFalseBranch();
protected:
    BasicBlock* true_branch;
    BasicBlock* false_branch;
};

class RetInstruction : public Instruction
{
public:
    RetInstruction(Operand *src, BasicBlock *insert_bb = nullptr);
    ~RetInstruction();
    std::vector<Operand *> getUse();
    void replaceUse(Operand* old, Operand* income);
    void output() const;
};

class CallInstruction : public Instruction
{
public:
    CallInstruction(Operand *dst, SymbolEntry *se, std::vector<Operand*> &args, BasicBlock *insert_bb = nullptr);
    ~CallInstruction();
    std::vector<Operand *> getUse();
    void replaceUse(Operand* old, Operand* income);
    void output() const;
private:
    SymbolEntry *se;
    std::vector<Operand*> args;
};

class SextInstruction : public Instruction
{
public:
    SextInstruction(Operand *dst, Operand *src, Type *toType, BasicBlock *insert_bb = nullptr);
    ~SextInstruction();
    std::vector<Operand *> getUse();
    void replaceUse(Operand* old, Operand* income);
    void output() const;
private:
    Type *toType;
};

class GepInstruction : public Instruction
{
public:
    GepInstruction(Operand *dst, Operand *src, std::vector<Operand*> &args, BasicBlock *insert_bb = nullptr);
    ~GepInstruction();
    void output() const;
private:
    std::vector<Operand*> args;
};

class PhiInstruction : public Instruction
{
public:
    PhiInstruction(Operand *dst, BasicBlock *insert_bb = nullptr);
    ~PhiInstruction();
    void addSrc(BasicBlock* block, Operand* src);
    Operand* getOriginDef() { return originDef; }
    // std::vector<Operand *> getUse();
    void replaceUse(Operand* old, Operand* income);
    // Operand* getDef();
    // void replaceDef(Operand* income);

    void output() const;

private:
    Operand* originDef;
    Operand* dst;
    std::map<BasicBlock*, Operand*> srcs;
};

#endif