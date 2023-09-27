#include <stdio.h>
#include "shell.h"
#include "mips_ins.h"
#include "mips_ins.c"

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
    // 获取当前指令
    uint32_t instruction = mem_read_32(CURRENT_STATE.PC);

    // 取指后就更新PC
    NEXT_STATE.PC += 4;
    
    // 解析指令
    // 1. 获取指令的opcode
    uint8_t opcode = (instruction >> 26) & 0x3F;
    // 2. 获取指令的rs
    uint8_t rs = (instruction >> 21) & 0x1F;
    // 3. 获取指令的rt
    uint8_t rt = (instruction >> 16) & 0x1F;
    // 4. 获取指令的rd
    uint8_t rd = (instruction >> 11) & 0x1F;
    // 5. 获取指令的shamt
    uint8_t shamt = (instruction >> 6) & 0x1F;
    // 6. 获取指令的funct
    uint8_t funct = instruction & 0x3F;
    // 7. 获取指令的immediate
    uint16_t immediate = instruction & 0xFFFF;
    // 8. 获取指令的address
    uint32_t address = instruction & 0x3FFFFFF;

    // 根据opcode分情况处理指令
    if(instruction == 0)
        nop();
    else if (opcode == 0x00)
        r_ins(rs, rt, rd, shamt, funct);
    else if (opcode == 0x01)
        i_ins_branch_rt(rs, rt, immediate);
    else if (opcode == 0x02 || opcode == 0x03)
        j_ins(opcode, address);
    else
        i_ins(opcode, rs, rt, immediate);
}
