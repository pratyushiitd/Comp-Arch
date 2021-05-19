# Mips Assembly program to evaluate a Postfix Expression

# -----------------------------------------------------

# Data Declarations

.data 

    prompt:         .asciiz     "This evaluates postfix expressions to corresponding value.\nAccepted characters in expressions are 0 to 9 integers and * + - operators.\nEnter the Postfix Expression: "
    result:         .asciiz     "The Expression evaluates to: "
    lengthIs:       .asciiz     "Length of exp is: "
    buffer:         .space      100
    endl:           .asciiz     "\n"
    add2:           .asciiz     "Adding: "
    mult2:          .asciiz     "Multiplying: "
    substr2:        .asciiz     "Subtracting: "
    div2:           .asciiz     "dividing\n"
    errormsg:       .asciiz     "Invalid Postfix Expression. Enter expressions with 0-9 integers and * + - operators only"
    stack_emt:      .asciiz     "Invalid Postfix Expression. Attempted to pop from empty stack"
    stack_nemt:     .asciiz     "Invalid Postfix Expression. Stack has more than 1 element after evaluation"     
    emptyInputmsg:  .asciiz     "Empty expression! If it is not by mistake then evaluates to 0"
    equals:         .asciiz     "= "
    ands:           .asciiz     " & "
    from:           .asciiz     " from "
    
# -----------------------------------------------------------
# Text / Code Section

.text
.globl  main
.ent    main
main:

    li		$v0, 4		
    la		$a0, prompt     # Displaying the prompt string
    syscall
    
    # Getting user's input
    li $v0, 8
    la $a0, buffer		# 
    li $a1, 100
    syscall
    move 	$s0, $a0
    move 	$s1, $s0

    # we have input string address in s0 and s1
    li      $s2, 0
    li      $s3, 2
    jal		stringLength				    # jump to stringLength and save position to $ra

    # now string length in s0
    # print length of the string
    
    jal		printLength				        # jump to printEnd and save position to $ra
    jal		printEnd				        # jump to printEnd and save position to $ra
    # Loop initialisation
    li		$t0, 0		                    # $t0 = 1 Loop iteral
    move 	$t1, $s1		                # $t1 = $s1 address
    beq		$s0, 0, emptyInput	# if $s0 == 0 then emptyInput
    forLoop:
        beq		$t0, $s0, exitFor	        # if $t0 == $s0 then exitFor
        
        lb		$a0, 0($t1)	
        beq		$a0, 42, multiplication	    # if $a0 == 43 then multiplication
        beq		$a0, 43, addition       	# if $a0 == 43 then addition
        beq		$a0, 45, subtraction	    # if $a0 == 45 then substract
        beq		$a0, 47, inputexception	    # if $a0 == 47 then division
        beq		$a0, 120, multiplication	# if $a0 == 120then multiplication
        blt     $a0, 48, inputexception	    # throw exception for ascii value below '0'
    	bgt	    $a0, 57, inputexception 	# throw exception for ascii value above '9'

        # andi $a0,$a0,0x0F
        add		$a0, $a0, -48		# $a0 = $a0 + 15
        # mul     $a0, $a0, 17

        jal		push_stack				# jump to push_stack and save position to $ra
        propForLoop:
            addi	$t1, $t1, 1			# $t1 = $t1 + 1
            addi	$t0, $t0, 1			# $t0 = $t0 + 1
            ble		$t0, $s0, forLoop	# if $t0 <= $s0 then forLoop
        
    exitFor:
        bne     $s2, 1, stack_nonemp
        la		$a0, result		# 
        li		$v0, 4		# $v0 = 4
        syscall
        lb		$a0, ($sp)	
        li		$v0, 1		# $v0 = 4
        syscall
        li		$v0, 10		# $v0 = 10
        syscall # all done!
.end main

stringLength:
    li		$t0, -1		# $t0 = 0
    loop:
        
        lb		$t1, 0($s0)		# 
        beqz    $t1, exit
        addi	$s0, $s0, 1			# $s0 = $s0 + 1
        addi	$t0, $t0, 1			# $t0 = $t0 + 1
        j		loop				# jump to loop
    exit:

        move 	$s0, $t0		    # $s0 = $t0
        jr		$ra					# jump to $ra
        
printEnd:
    li		$v0, 4		        # $v0 = 4
    la		$a0, endl		    #      
    syscall
    jr		$ra					# jump to $ra
printEquals:
    li		$v0, 4		        # $v0 = 4
    la		$a0, equals		    # 
    syscall
    jr		$ra					# jump to $ra
printAnd:
    li		$v0, 4		        # $v0 = 4
    la		$a0, ands		    # 
    syscall
    jr		$ra					# jump to $ra
printfrom:
    li		$v0, 4		        # $v0 = 4
    la		$a0, from		    # 
    syscall
    jr		$ra					# jump to $ra


printLength:
    li		$v0, 4		# $v0 = 4
    la		$a0, lengthIs		# 
    syscall
    li		$v0, 1		# $v0 = 4
    move	$a0, $s0		# 
    syscall
    jr		$ra					# jump to $ra

inputexception:
    li		$v0, 4		# $v0 = 4
    la		$a0, errormsg		# 
    syscall
    li		$v0, 10		# $v0 = 10
    syscall # all done!

stack_empty:

    li		$v0, 4		# $v0 = 4
    la		$a0, stack_emt		# 
    syscall
    li		$v0, 10		# $v0 = 10
    syscall 

emptyInput:
    li		$v0, 4		# $v0 = 4
    la		$a0, emptyInputmsg		# 
    syscall
    li		$v0, 10		# $v0 = 10
    syscall

stack_nonemp:

    li		$v0, 4		# $v0 = 4
    la		$a0, stack_nemt		# 
    syscall
    li		$v0, 10		# $v0 = 10
    syscall 

addition:

    li		$v0, 4		# $v0 = 4
    la		$a0, add2		# 
    syscall    
    jal		pop_stack				# jump to pop_stack and save position to $ra
    
    li		$v0, 1		# $v0 = 1
    move 	$a0, $t3		# $a0 = $t3
    syscall
    jal		printAnd				# jump to printAnd and save position to $ra
    
    li		$v0, 1		# $v0 = 1
    move 	$a0, $t4		# $a0 = $t3
    syscall
    jal		printEnd				# jump to printEnd and save position to $ra
    jal		printEquals				# jump to printEquals and save position to $ra
    
    add		$a0, $t3, $t4		# $t3 = $t3 + $t4
    li		$v0, 1		# $v0 = 4
    syscall
    jal		push_stack				# jump to push_stack and save position to $ra
    jal		printEnd				# jump to printEnd and save position to $ra


    j		propForLoop				# jump to forLoop

subtraction:

    li		$v0, 4		# $v0 = 4
    la		$a0, substr2		# 
    syscall
    jal		pop_stack				# jump to pop_stack and save position to $ra
    li		$v0, 1		# $v0 = 1
    move 	$a0, $t3		# $a0 = $t4
    syscall
    jal		printfrom				# jump to printAnd and save position to $ra
    li		$v0, 1		# $v0 = 1
    move 	$a0, $t4		# $a0 = $t3
    syscall
    jal		printEnd				# jump to printEnd and save position to $ra
    jal		printEquals				# jump to printEquals and save position to $ra
    
    sub		$a0, $t4, $t3		# $t3 = $t3 + $t4
    li		$v0, 1		# $v0 = 4
    syscall
    jal		push_stack				# jump to push_stack and save position to $ra
    jal		printEnd				# jump to printEnd and save position to $ra
    

    j		propForLoop				# jump to forLoop

multiplication:
    
    li		$v0, 4		# $v0 = 4
    la		$a0, mult2		# 
    syscall
    jal		pop_stack				# jump to pop_stack and save position to $ra
    li		$v0, 1		# $v0 = 1
    move 	$a0, $t3		# $a0 = $t3
    syscall
    jal		printAnd				# jump to printAnd and save position to $ra
    li		$v0, 1		# $v0 = 1
    move 	$a0, $t4		# $a0 = $t3
    syscall
    jal		printEnd				# jump to printEnd and save position to $ra
    jal		printEquals				# jump to printEquals and save position to $ra
    
    mul		$a0, $t3, $t4		# $t3 = $t3 + $t4
    li		$v0, 1		# $v0 = 4
    syscall
    jal		push_stack				# jump to push_stack and save position to $ra
    jal		printEnd				# jump to printEnd and save position to $ra

    j		propForLoop				# jump to forLoop

divide:
    li		$v0, 4		# $v0 = 4
    la		$a0, div2		# 
    syscall
    addi	$t1, $t1, 1			# $t1 = $t1 + 1
    addi	$t0, $t0, 1			# $t0 = $t0 + 1
    j		forLoop				# jump to forLoop

push_stack:
    add     $s2, $s2, 1
    subu    $sp, $sp, 4
    sw		$a0, ($sp)		# 
    jr		$ra					# jump to $ra
    
pop_stack:
    blt $s2, $s3, stack_empty
    lb		$t3, ($sp)		# 
    lb		$t4, 4($sp)		# 
    addu    $sp, $sp, 8
    sub $s2, $s2, $s3
    jr		$ra					# jump to $ra