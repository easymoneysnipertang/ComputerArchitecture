# MIPS Assembly Program

# Text Section
.text
.globl main

main:
    # Jump to Label 1
    j label1

    # This code is skipped
    addi $t0, $zero, 1      # $t0 = 1

label1:
    # Some instructions here
    addi $t1, $zero, 2      # $t1 = 2

    # Jump to Label 2
    j label2

    # This code is skipped
    addi $t2, $zero, 3      # $t2 = 3

label2:
    # Some instructions here
    add $t3, $t0, $t1       # $t3 = $t0 + $t1

    # Exit
    li $v0, 10               # Load 10 into $v0 (exit program)
    syscall
