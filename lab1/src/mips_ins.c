#include "mips_ins.h"
#include "shell.h"
#include <stdio.h>

void nop(){
    // 空指令
    return;
}

void syscall(){
    // 系统调用
    if(CURRENT_STATE.REGS[2] == 0x0A)
        RUN_BIT = 0;  // 退出程序
}

void sll(uint8_t rt, uint8_t rd, uint8_t shamt){
    // 逻辑左移
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shamt;
}

void srl(uint8_t rt, uint8_t rd, uint8_t shamt){
    // 逻辑右移
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
}

void sra(uint8_t rt, uint8_t rd, uint8_t shamt){
    // 算数右移，高位填充符号位
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rt] >> shamt;
}

void sllv(uint8_t rs, uint8_t rt, uint8_t rd){
    // 逻辑左移，移位数由rs给出，&0x1F确保移位数不超过31
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << (CURRENT_STATE.REGS[rs] & 0x1F);
}

void srlv(uint8_t rs, uint8_t rt, uint8_t rd){
    // 逻辑右移，移位数由rs给出，&0x1F确保移位数不超过31
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> (CURRENT_STATE.REGS[rs] & 0x1F);
}

void srav(uint8_t rs, uint8_t rt, uint8_t rd){
    // 算数右移，移位数由rs给出，&0x1F确保移位数不超过31，高位填充符号位
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rt] >> (CURRENT_STATE.REGS[rs] & 0x1F);
}

void jr(uint8_t rs){
    // 无条件跳转，跳转地址由rs给出
    NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
}

void jalr(uint8_t rs, uint8_t rd){
    // 无条件跳转，跳转地址由rs给出，同时将PC+4写入rd
    // 如果没有在指令中指明rd，那么默认将返回地址保存到寄存器$31
    uint8_t d = rd == 0? 31: rd;
    NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
    NEXT_STATE.REGS[d] = CURRENT_STATE.PC + 4;  // TODO: check
}

void mfhi(uint8_t rd){
    // 将HI寄存器的值写入rd
    if(rd != 0)
        NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
}

void mthi(uint8_t rs){
    // 将rs的值写入HI寄存器
    CURRENT_STATE.HI = CURRENT_STATE.REGS[rs];
}

void mflo(uint8_t rd){
    // 将LO寄存器的值写入rd
    if(rd != 0)
        NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;
}

void mtlo(uint8_t rs){
    // 将rs的值写入LO寄存器
    CURRENT_STATE.LO = CURRENT_STATE.REGS[rs];
}

void mult(uint8_t rs, uint8_t rt){
    // 有符号乘法，结果保存在HI和LO寄存器中
    int64_t result = (int64_t)CURRENT_STATE.REGS[rs] * (int64_t)CURRENT_STATE.REGS[rt];
    NEXT_STATE.HI = result >> 32;
    NEXT_STATE.LO = result & 0xFFFFFFFF;
}

void multu(uint8_t rs, uint8_t rt){
    // 无符号乘法，结果保存在HI和LO寄存器中
    uint64_t result = (uint64_t)CURRENT_STATE.REGS[rs] * (uint64_t)CURRENT_STATE.REGS[rt];
    NEXT_STATE.HI = result >> 32;
    NEXT_STATE.LO = result & 0xFFFFFFFF;
}

void div(uint8_t rs, uint8_t rt){
    // 有符号除法，结果保存在HI和LO寄存器中
    NEXT_STATE.LO = (int32_t)CURRENT_STATE.REGS[rs] / (int32_t)CURRENT_STATE.REGS[rt];
    NEXT_STATE.HI = (int32_t)CURRENT_STATE.REGS[rs] % (int32_t)CURRENT_STATE.REGS[rt];
}

void divu(uint8_t rs, uint8_t rt){
    // 无符号除法，结果保存在HI和LO寄存器中
    NEXT_STATE.LO = (uint32_t)CURRENT_STATE.REGS[rs] / (uint32_t)CURRENT_STATE.REGS[rt];
    NEXT_STATE.HI = (uint32_t)CURRENT_STATE.REGS[rs] % (uint32_t)CURRENT_STATE.REGS[rt];
}

void add(uint8_t rs, uint8_t rt, uint8_t rd){
    // 有符号加法，溢出时报错
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rs] + (int32_t)CURRENT_STATE.REGS[rt];
    if(((int32_t)CURRENT_STATE.REGS[rs] > 0 && (int32_t)CURRENT_STATE.REGS[rt] > 0 && (int32_t)NEXT_STATE.REGS[rd] < 0) ||
         ((int32_t)CURRENT_STATE.REGS[rs] < 0 && (int32_t)CURRENT_STATE.REGS[rt] < 0 && (int32_t)NEXT_STATE.REGS[rd] > 0))
          printf("Error: signed integer overflow in add\n");
}

void addu(uint8_t rs, uint8_t rt, uint8_t rd){
    // 无符号加法，溢出时不报错
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rs] + (int32_t)CURRENT_STATE.REGS[rt];
    // The only difference between this instruction and the ADD instruction is
    // that ADDU never causes an overflow exception
}

void sub(uint8_t rs, uint8_t rt, uint8_t rd){
    // 有符号减法，溢出时报错
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rs] - (int32_t)CURRENT_STATE.REGS[rt];
    if(((int32_t)CURRENT_STATE.REGS[rs] > 0 && (int32_t)CURRENT_STATE.REGS[rt] < 0 && (int32_t)NEXT_STATE.REGS[rd] < 0) ||
         ((int32_t)CURRENT_STATE.REGS[rs] < 0 && (int32_t)CURRENT_STATE.REGS[rt] > 0 && (int32_t)NEXT_STATE.REGS[rd] > 0))
          printf("Error: signed integer overflow in sub\n");
}

void subu(uint8_t rs, uint8_t rt, uint8_t rd){
    // 无符号减法，溢出时不报错
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rs] - (int32_t)CURRENT_STATE.REGS[rt];
}

void and(uint8_t rs, uint8_t rt, uint8_t rd){
    // 逻辑与
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
}

void or(uint8_t rs, uint8_t rt, uint8_t rd){
    // 逻辑或
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
}

void xor(uint8_t rs, uint8_t rt, uint8_t rd){
    // 逻辑异或
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt];
}

void nor(uint8_t rs, uint8_t rt, uint8_t rd){
    // 逻辑或非
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
}

void slt(uint8_t rs, uint8_t rt, uint8_t rd){
    // 有符号比较，rs<rt时rd=1，否则rd=0
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rs] < (int32_t)CURRENT_STATE.REGS[rt];
}

void sltu(uint8_t rs, uint8_t rt, uint8_t rd){
    // 无符号比较，rs<rt时rd=1，否则rd=0
    if(rd != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt];
}

void bltz(uint8_t rs, int16_t offset){
    // 当rs<0时跳转
    if((int32_t)CURRENT_STATE.REGS[rs] < 0)
        // 字节寻址，左移2位；在PC+4基础上偏移
        NEXT_STATE.PC = NEXT_STATE.PC + (offset << 2);
}

void bgez(uint8_t rs, int16_t offset){
    // 当rs>=0时跳转
    if((int32_t)CURRENT_STATE.REGS[rs] >= 0)
        // 字节寻址，左移2位；在PC+4基础上偏移
        NEXT_STATE.PC = NEXT_STATE.PC + (offset << 2);
}

void bltzal(uint8_t rs, int16_t offset){
    // 当rs<0时跳转，同时将PC+4写入$31
    if((int32_t)CURRENT_STATE.REGS[rs] < 0){
        // 字节寻址，左移2位；在PC+4基础上偏移
        NEXT_STATE.PC = NEXT_STATE.PC + (offset << 2);
        NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4; // TODO: check
    }
}

void bgezal(uint8_t rs, int16_t offset){
    // 当rs>=0时跳转，同时将PC+4写入$31
    if((int32_t)CURRENT_STATE.REGS[rs] >= 0){
        // 字节寻址，左移2位；在PC+4基础上偏移
        NEXT_STATE.PC = NEXT_STATE.PC + (offset << 2);
        NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4; // TODO: check
    }
}

void beq(uint8_t rs, uint8_t rt, int16_t offset){
    // 当rs=rt时跳转
    if(CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt])
        // 字节寻址，左移2位；在PC+4基础上偏移
        NEXT_STATE.PC = NEXT_STATE.PC + (offset << 2) ;
}

void bne(uint8_t rs, uint8_t rt, int16_t offset){
    // 当rs!=rt时跳转
    if(CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt])
        // 字节寻址，左移2位；在PC+4基础上偏移
        NEXT_STATE.PC = NEXT_STATE.PC + (offset << 2);
}

void blez(uint8_t rs, int16_t offset){
    // 当rs<=0时跳转
    if((int32_t)CURRENT_STATE.REGS[rs] <= 0)
        // 字节寻址，左移2位；在PC+4基础上偏移
        NEXT_STATE.PC = NEXT_STATE.PC + (offset << 2);
}

void bgtz(uint8_t rs, int16_t offset){
    // 当rs>0时跳转
    if((int32_t)CURRENT_STATE.REGS[rs] > 0)
        // 字节寻址，左移2位；在PC+4基础上偏移
        NEXT_STATE.PC = NEXT_STATE.PC + (offset << 2);
}

void addi(uint8_t rs, uint8_t rt, int16_t imm){
    // 有符号加法，溢出时报错
    if(rt != 0){  // 目标寄存器不能为0
        int32_t imm32 = imm > 0x7FFF? imm | 0xFFFF0000: imm;  // 符号拓展老不行
        NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + imm32;
    }
    if(((int32_t)CURRENT_STATE.REGS[rs] > 0 && imm > 0 && (int32_t)NEXT_STATE.REGS[rt] < 0) ||
         ((int32_t)CURRENT_STATE.REGS[rs] < 0 && imm < 0 && (int32_t)NEXT_STATE.REGS[rt] > 0))
          printf("Error: signed integer overflow in addi\n");
}

void addiu(uint8_t rs, uint8_t rt, uint16_t imm){
    // 无符号加法，溢出时不报错
    if(rt != 0){  // 目标寄存器不能为0
        int32_t imm32 = imm > 0x7FFF? imm | 0xFFFF0000: imm;
        NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + imm32;
    }
}

void slti(uint8_t rs, uint8_t rt, int16_t imm){
    // 有符号比较，rs<imm时rt=1，否则rt=0
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rt] = (int32_t)CURRENT_STATE.REGS[rs] < (int32_t)imm;
}

void sltiu(uint8_t rs, uint8_t rt, uint16_t imm){
    // 无符号比较，rs<imm时rt=1，否则rt=0
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] < (int32_t)imm;
}

void andi(uint8_t rs, uint8_t rt, int16_t imm){
    // 逻辑与，高位填充0
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] & (imm & 0x0000FFFF);
}

void ori(uint8_t rs, uint8_t rt, int16_t imm){
    // 逻辑或，高位填充0
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | (imm & 0x0000FFFF);
}

void xori(uint8_t rs, uint8_t rt, int16_t imm){
    // 逻辑异或，高位填充0
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] ^ (imm & 0x0000FFFF);
}

void lui(uint8_t rt, int16_t imm){
    // 将imm的高16位写入rt，低16位填充0
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rt] = (uint32_t)imm << 16;
}

void lb(uint8_t base, uint8_t rt, int16_t offset){
    // 从rs+offset处读取一个字节，符号扩展后写入rt
    if(rt != 0){ // 目标寄存器不能为0
        uint32_t addr = (int32_t)CURRENT_STATE.REGS[base] + offset;
        uint32_t temp = mem_read_32(addr) & 0xFF;
        // int_32t转不过来，符号拓展很麻烦
        NEXT_STATE.REGS[rt] = temp > 0x7F? temp | 0xFFFFFF00: temp;
    }
}

void lh(uint8_t base, uint8_t rt, int16_t offset){
    // 从rs+offset处读取两个字节，符号扩展后写入rt
    if(rt != 0){ // 目标寄存器不能为0
        uint32_t addr = (int32_t)CURRENT_STATE.REGS[base] + offset;
        uint32_t temp = mem_read_32(addr) & 0xFFFF;
        // int_32t转不过来
        NEXT_STATE.REGS[rt] = temp > 0x7FFF? temp | 0xFFFF0000: temp;
    }
}

void lw(uint8_t base, uint8_t rt, int16_t offset){
    // 从rs+offset处读取四个字节，写入rt
    if(rt != 0)  // 目标寄存器不能为0
        NEXT_STATE.REGS[rt] = mem_read_32((int32_t)CURRENT_STATE.REGS[base] + offset);
}

void lbu(uint8_t base, uint8_t rt, int16_t offset){
    // 从rs+offset处读取一个字节，零扩展后写入rt
    if(rt != 0){ // 目标寄存器不能为0
        uint32_t addr = (int32_t)CURRENT_STATE.REGS[base] + offset;
        NEXT_STATE.REGS[rt] = (uint32_t) (mem_read_32(addr) & 0x000000FF);
    }
}

void lhu(uint8_t base, uint8_t rt, int16_t offset){
    // 从rs+offset处读取两个字节，零扩展后写入rt
    if(rt != 0){ // 目标寄存器不能为0
        uint32_t addr = (int32_t)CURRENT_STATE.REGS[base] + offset;
        NEXT_STATE.REGS[rt] = (uint32_t) (mem_read_32(addr) & 0x0000FFFF);
    }
}

void sb(uint8_t base, uint8_t rt, int16_t offset){
    // 将rt的低8位写入rs+offset处
    uint32_t addr = (int32_t)CURRENT_STATE.REGS[base] + offset;
    // 一次写32位，需要保留原地址其他位
    uint32_t data = mem_read_32(addr) & 0xFFFFFF00;  // 低位置0
    data |= CURRENT_STATE.REGS[rt] & 0xFF;
    mem_write_32(addr, data);
}

void sh(uint8_t base, uint8_t rt, int16_t offset){
    // 将rt的低16位写入rs+offset处
    uint32_t addr = (int32_t)CURRENT_STATE.REGS[base] + offset;
    // 一次写32位，需要保留原地址其他位
    uint32_t data = mem_read_32(addr) & 0xFFFF0000;  // 低位置0
    data |= CURRENT_STATE.REGS[rt] & 0xFFFF;
    mem_write_32(addr, data);
}

void sw(uint8_t base, uint8_t rt, int16_t offset){
    // 将rt写入rs+offset处
    mem_write_32((int32_t)CURRENT_STATE.REGS[base] + offset, CURRENT_STATE.REGS[rt]);
}

void j(uint32_t addr){
    // 无条件跳转，PC的高四位不变，低28位由addr给出
    NEXT_STATE.PC = (NEXT_STATE.PC & 0xF0000000) | (addr << 2);
}

void jal(uint32_t addr){
    // 无条件跳转，PC的高四位不变，低28位由addr给出，同时将PC+4写入$31
    NEXT_STATE.PC = (NEXT_STATE.PC & 0xF0000000) | (addr << 2);
    NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4; // TODO: check
}

// 指令分发处理
void r_ins(uint8_t rs, uint8_t rt, uint8_t rd, uint8_t shamt, uint8_t funct){
    switch (funct)
    {
    // 移位指令
    case SLL:
        sll(rt, rd, shamt);
        break;
    case SRL:
        srl(rt, rd, shamt);
        break;
    case SRA: 
        sra(rt, rd, shamt);
        break;
    case SLLV:
        sllv(rs, rt, rd);
        break;
    case SRLV:
        srlv(rs, rt, rd);
        break;
    case SRAV:
        srav(rs, rt, rd);
        break;
    // 跳转指令
    case JR:
        jr(rs);
        break;
    case JALR:
        jalr(rs, rd);
        break;
    // 移动指令
    case MFHI:
        mfhi(rd);
        break;
    case MTHI:
        mthi(rs);
        break;
    case MFLO:
        mflo(rd);
        break;
    case MTLO:
        mtlo(rs);
        break;
    // 算数指令
    case MULT:
        mult(rs, rt);
        break;
    case MULTU:
        multu(rs, rt);
        break;
    case DIV:
        div(rs, rt);
        break;
    case DIVU:
        divu(rs, rt);
        break;
    case ADD:
        add(rs, rt, rd);
        break;
    case ADDU:
        addu(rs, rt, rd);
        break;
    case SUB:
        sub(rs, rt, rd);
        break;
    case SUBU:
        subu(rs, rt, rd);
        break;
    // 逻辑指令
    case AND:
        and(rs, rt, rd);
        break;
    case OR:
        or(rs, rt, rd);
        break;
    case XOR:
        xor(rs, rt, rd);
        break;
    case NOR:
        nor(rs, rt, rd);
        break;
    // 比较指令
    case SLT:
        slt(rs, rt, rd);
        break;
    case SLTU:
        sltu(rs, rt, rd);
        break;
    case SYSCALL:
        syscall();
        break;
    }
}

void i_ins(uint8_t opcode, uint8_t rs, uint8_t rt, int16_t imm){
    switch (opcode)
    {
    // 分支跳转
    case BEQ:
        beq(rs, rt, imm);
        break;
    case BNE:
        bne(rs, rt, imm);
        break;
    case BLEZ:
        blez(rs, imm);
        break;
    case BGTZ:
        bgtz(rs, imm);
        break;
    // 算数运算
    case ADDI:
        addi(rs, rt, imm);
        break;
    case ADDIU:   
        addiu(rs, rt, imm);
        break;
    case SLTI:
        slti(rs, rt, imm);
        break;
    case SLTIU:
        sltiu(rs, rt, imm);
        break;
    case ANDI:
        andi(rs, rt, imm);
        break;
    case ORI:
        ori(rs, rt, imm);
        break;
    case XORI: 
        xori(rs, rt, imm);
        break;
    case LUI:
        lui(rt, imm);
        break;
    // 内存访问
    case LB:
        lb(rs, rt, imm);
        break;
    case LH:
        lh(rs, rt, imm);
        break;
    case LW:
        lw(rs, rt, imm);
        break;
    case LBU:
        lbu(rs, rt, imm);
        break;
    case LHU:
        lhu(rs, rt, imm);
        break;
    case SB:
        sb(rs, rt, imm);
        break;
    case SH:
        sh(rs, rt, imm);
        break;
    case SW:
        sw(rs, rt, imm);
        break;
    }
}

void i_ins_branch_rt(uint8_t rs, uint8_t rt, int16_t offset){
    switch (rt)
    {
    case BLTZ:
        bltz(rs, offset);
        break;
    case BGEZ:
        bgez(rs, offset);
        break;
    case BLTZAL:
        bltzal(rs, offset);
        break;
    case BGEZAL:    
        bgezal(rs, offset);
        break;
    }
}

void j_ins(uint8_t opcode, uint32_t addr){
    switch (opcode)
    {
    case J:
        j(addr);
        break;
    case JAL:
        jal(addr);
        break;
    }
}