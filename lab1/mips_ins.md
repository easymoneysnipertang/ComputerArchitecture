# MIPS指令分类
## R型

### shifts
逻辑移位在移位操作中不考虑数值的符号位  
算术移位会考虑数值的符号位，保持符号位不变，并将其扩展到移位后的高位或低位  
- SLL (shift left logical)  
`sll $rd, $rt, shamt`
- SRL (shift right logical)  
`srl $rd, $rt, shamt`
- SRA (shift right arithmetic)  
`sra $rd, $rt, shamt`
- SLLV (shift left logical variable)  
`sllv $rd, $rt, $rs`
- SRLV (shift right logical variable)  
`srlv $rd, $rt, $rs`
- SRAV (shift right arithmetic variable)  
`srav $rd, $rt, $rs`

### conditional
- SLT (set on less than)  
`slt $rd, $rs, $rt`
- SLTU (set on less than unsigned)  
`sltu $rd, $rs, $rt`

### r_jump
- jr (jump register)  
`jr $rs`
- jalr (jump and link register)  
`jalr $rd, $rs`  
"$rd" 是目标寄存器，用于保存返回地址  
"$rs" 是要从中读取目标地址的寄存器

### r_lo_hi
- mfhi (move from hi)  
`mfhi $rd`  
"$rd" 是目标寄存器，用于保存 Hi 寄存器的值
- mflo (move from lo)  
`mflo $rd`
- mthi (move to hi)  
`mthi $rs`   
"$rs" 是源寄存器，其值将被复制到 Hi 寄存器中
- mtlo (move to lo)  
`mtlo $rs`

### logical
- and  
`and $rd, $rs, $rt`
- or  
`or $rd, $rs, $rt`
- nor  
`nor $rd, $rs, $rt`
- xor  
`xor $rd, $rs, $rt`

### arithmetic
- add 
- addu
- sub
- subu
- mult  
将两个有符号整数相乘，并将结果存储在Hi寄存器和Lo寄存器  
`mult $rs, $rt`
- multu  
`multu $rs, $rt`
- div  
将一个有符号整数除以另一个有符号整数，将商存储在Lo寄存器中，将余数存储在Hi寄存器中  
`div $rs, $rt`
- divu  
`divu $rs, $rt`


## I型
### branch
- beq (branch if equal)  
`beq $rs, $rt, offset`
- bneq (branch if not equal)  
`bne $rs, $rt, offset`
- blez (branch if less than or equal to zero)  
`blez $rs, offset`
- bltz (branch if less than to zero)
- bgez (branch if greater than or equal to zero)
- bgtz (branch if greater than to zero)  
`bgtz $rs, offset`
- bltzal (branch if less than zero and link)  
`bltzal $rs, offset`
- bgezal (branch if greater than or equal to zero and link)

### i_arithmetic
- addi (add immediate)  
`addi $rt, $rs, immediate`
- addiu (add immediate unsigned)  
- slti (set on less than immediate)  
`slti $rt, $rs, immediate`
- sltiu (set on less than immediate unsigned)
- andi  
将一个寄存器中的值与一个立即数进行按位与运算，并将结果存储在目标寄存器中  
`andi $rt, $rs, immediate`
- ori
- xori
- lui (load upper immediate)  
加载高16位到寄存器  
`lui $rt, immediate`

### memory
- lb (load byte)  
`lb $rt, offset($rs)`
- lh (load halfword)  
- lw (load word)
- lbu (load byte unsigned)
- lhu (load halfword unsigned)
- sb (store byte)
- sh (store halfword)
- sw (store word)

## J型
- j (jump)  
`j target`
- jal (jump and link)  
`jal target`