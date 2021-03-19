# MIPS Assembly Program for evaluating an expression in postfix format

# -------------------------

# Data Declarations

.data 

    prompt:     .asciiz     "Enter the Postfix Expression: "
    result:     .asciiz     "The Expression evaluates to: "
    buffer:     .space      100
# -------------------------
# Text / Code Section

.text
.globl  main
.ent    main
main:

    li		$v0, 4		
    la		$a0, prompt 
    syscall

    # Getting user's input
    li $v0, 8
    la $a0, buffer		# 
    li $a1, 100
    
    
    syscall
    
    move 	$s0, $a0		# $s0 = $a0
    jal		stringLength				# jump to stringLength and save position to $ra
    
    li		$v0, 1		# $v0 = 4
    move		$a0, $s1		# 
    syscall
    # forLoop:
        # lw		$t4, 0($s0)		# 
        # subu	$sp, $sp, 4
        # sw		$t4, ($sp)		# 
        lb		$t1, 0($s1)		# 
        
        andi $t1,$t1,0x0F
        li		$v0, 1		
        move 	$a0, $t1		# $a0 = $t1
        syscall


    la		$a0, result		# 
    li		$v0, 4		# $v0 = 4
    syscall

    la		$a0, buffer		# 
    li		$v0, 4		# $v0 = 4
    syscall
        li		$v0, 10		# $v0 = 10
        syscall # all done!
.end main

stringLength:
    li		$t0, 0		# $t0 = 0
    loop:
        
        lb		$t1, 0($s0)		# 
        beqz    $t1, exit
        addi	$s0, $s0, 1			# $s0 = $s0 + 1
        addi	$t0, $t0, 1			# $t0 = $t0 + 1
        j		loop				# jump to loop
    exit:
        move 	$s1, $t0		# $s1 = $s0
        jr		$ra					# jump to $ra
        