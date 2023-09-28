# MIPS Assembly Program

# Data Section
.data
msg: .asciiz "Hello, MIPS!\n"   # A string to print

# Text Section
.text
.globl main

main:
    # Arithmetic Operations
    addi $t0, $zero, 5      # $t0 = 5
    addi $t1, $zero, 3      # $t1 = 3
    add $t2, $t0, $t1       # $t2 = $t0 + $t1
    sub $t3, $t0, $t1       # $t3 = $t0 - $t1

    # Multiplication and Division
    li $t0, 5               # $t0 = 5
    li $t1, 3               # $t1 = 3
    mult $t0, $t1           # $t0 * $t1, result in HI and LO
    mflo $t4                # $t4 = LO (result of multiplication)
    mfhi $t5                # $t5 = HI (result of multiplication)

    div $t0, $t1            # $t0 / $t1, result in HI and LO
    mflo $t6                # $t6 = LO (result of division)
    mfhi $t7                # $t7 = HI (result of division)

    # Print Results
    li $v0, 1                # Load 1 into $v0 (print integer)
    move $a0, $t4            # Move $t4 (result of multiplication) into $a0
    syscall

    move $a0, $t5            # Move $t5 (HI of multiplication) into $a0
    syscall

    move $a0, $t6            # Move $t6 (result of division) into $a0
    syscall

    move $a0, $t7            # Move $t7 (HI of division) into $a0
    syscall

    # Print a string
    li $v0, 4                # Load 4 into $v0 (print string)
    la $a0, msg              # Load address of the string into $a0
    syscall

    # Exit
    li $v0, 10               # Load 10 into $v0 (exit program)
    syscall
