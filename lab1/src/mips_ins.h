#ifndef MIPS_INS_h
#define MIPS_INS_h

#include <stdint.h>


// --------------------R型指令--------------------
// OP=0x00(SPECIAL)，区分function code
// 移位指令
#define SLL 0x00
#define SRL 0x02
#define SRA 0x03
#define SLLV 0x04
#define SRLV 0x06
#define SRAV 0x07
// 跳转指令
#define JR 0x08
#define JALR 0x09
// 移动指令
#define MFHI 0x10
#define MTHI 0x11
#define MFLO 0x12
#define MTLO 0x13
// 算数指令
#define MULT 0x18
#define MULTU 0x19
#define DIV 0x1A
#define DIVU 0x1B
#define ADD 0x20
#define ADDU 0x21
#define SUB 0x22
#define SUBU 0x23
// 逻辑运算
#define AND 0x24
#define OR 0x25
#define XOR 0x26
#define NOR 0x27
// 条件置位
#define SLT 0x2A
#define SLTU 0x2B


// --------------------I型指令--------------------
// OP=0x01(REGIMM)，区分rt
#define BLTZ 0x00
#define BGEZ 0x01
#define BLTZAL 0x10
#define BGEZAL 0x11

// 区分OP
// 分支跳转
#define BEQ 0x04
#define BNE 0x05
#define BLEZ 0x06
#define BGTZ 0x07
// 算数运算
#define ADDI 0x08
#define ADDIU 0x09
#define SLTI 0x0A
#define SLTIU 0x0B
#define ANDI 0x0C
#define ORI 0x0D
#define XORI 0x0E
#define LUI 0x0F
// 内存访问
#define LB 0x20
#define LH 0x21
#define LW 0x23
#define LBU 0x24
#define LHU 0x25
#define SB 0x28
#define SH 0x29
#define SW 0x2B

// --------------------J型指令--------------------
// 区分OP
#define J 0x02
#define JAL 0x03

#define SYSCALL 0x0C // OP=0x00(SPECIAL)，function code=0x0C


// instructions
void nop();
void syscall();


// --------------------R型指令--------------------
void r_ins(uint8_t rs, uint8_t rt, uint8_t rd, uint8_t shamt, uint8_t funct);

// 移位指令
void sll(uint8_t rt, uint8_t rd, uint8_t shamt);
void srl(uint8_t rt, uint8_t rd, uint8_t shamt);
void sra(uint8_t rt, uint8_t rd, uint8_t shamt);
void sllv(uint8_t rs, uint8_t rt, uint8_t rd);
void srlv(uint8_t rs, uint8_t rt, uint8_t rd);
void srav(uint8_t rs, uint8_t rt, uint8_t rd);
// 跳转指令
void jr(uint8_t rs);
void jalr(uint8_t rs, uint8_t rd);
// 移动指令
void mfhi(uint8_t rd);
void mthi(uint8_t rs);
void mflo(uint8_t rd);
void mtlo(uint8_t rs);
// 算数指令
void mult(uint8_t rs, uint8_t rt);
void multu(uint8_t rs, uint8_t rt);
void div(uint8_t rs, uint8_t rt);
void divu(uint8_t rs, uint8_t rt);
void add(uint8_t rs, uint8_t rt, uint8_t rd);
void addu(uint8_t rs, uint8_t rt, uint8_t rd);
void sub(uint8_t rs, uint8_t rt, uint8_t rd);
void subu(uint8_t rs, uint8_t rt, uint8_t rd);
// 逻辑运算
void and(uint8_t rs, uint8_t rt, uint8_t rd);
void or(uint8_t rs, uint8_t rt, uint8_t rd);
void xor(uint8_t rs, uint8_t rt, uint8_t rd);
void nor(uint8_t rs, uint8_t rt, uint8_t rd);
// 条件置位
void slt(uint8_t rs, uint8_t rt, uint8_t rd);
void sltu(uint8_t rs, uint8_t rt, uint8_t rd);


// --------------------I型指令--------------------
void i_ins_branch_rt(uint8_t rs, uint8_t rt, int16_t offset);

// 判断分支
void bltz(uint8_t rs, int16_t offset);
void bgez(uint8_t rs, int16_t offset);
void bltzal(uint8_t rs, int16_t offset);
void bgezal(uint8_t rs, int16_t offset);

void i_ins(uint8_t opcode, uint8_t rs, uint8_t rt, int16_t imm);

// 分支跳转
void beq(uint8_t rs, uint8_t rt, int16_t offset);
void bne(uint8_t rs, uint8_t rt, int16_t offset);
void blez(uint8_t rs, int16_t offset);
void bgtz(uint8_t rs, int16_t offset);
// 算数运算
void addi(uint8_t rs, uint8_t rt, int16_t imm);
void addiu(uint8_t rs, uint8_t rt, uint16_t imm);
void slti(uint8_t rs, uint8_t rt, int16_t imm);
void sltiu(uint8_t rs, uint8_t rt, uint16_t imm);
void andi(uint8_t rs, uint8_t rt, int16_t imm);
void ori(uint8_t rs, uint8_t rt, int16_t imm);
void xori(uint8_t rs, uint8_t rt, int16_t imm);
void lui(uint8_t rt, int16_t imm);
// 内存访问
void lb(uint8_t base, uint8_t rt, int16_t offset);
void lh(uint8_t base, uint8_t rt, int16_t offset);
void lw(uint8_t base, uint8_t rt, int16_t offset);
void lbu(uint8_t base, uint8_t rt, int16_t offset);
void lhu(uint8_t base, uint8_t rt, int16_t offset);
void sb(uint8_t base, uint8_t rt, int16_t offset);
void sh(uint8_t base, uint8_t rt, int16_t offset);
void sw(uint8_t base, uint8_t rt, int16_t offset);


// --------------------J型指令--------------------
void j_ins(uint8_t opcode, uint32_t addr);

void j(uint32_t addr);
void jal(uint32_t addr);


#endif