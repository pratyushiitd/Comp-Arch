# MIPS assembly program for obtaining the area under a curve formed by
# joining successive points by a straight line.

# -------------------------------------------------------

# Data declarations

.data 
	prompt:	    .asciiz	"Enter the number of Coordinates N : "
	result:	    .asciiz	"\nThe area under curve is: "
	     N:	    .word	0
	  area:	    .double	0.00

# --------------------------------------------------------

# Text/code section
.text
	.globl  main
main: 
	move $s1, $zero
	move $s2, $zero
	move $s3, $zero
	move $s4, $zero
	move $s5, $zero
	li.d $f10, 0.0			# f10 for area
	
# Reading N value from the user
	li	$v0, 4		# print prompt string
	la	$a0, prompt	
	syscall

	li	$v0, 5		# read N
	syscall
	move	$s1, $v0

	li $s0, 2
	li.d $f4, 2.0

beq $s1, 0, exit_func 		# Check N = 0
# Reading first coordinate
	li	$v0, 5
	syscall
	move	$t2, $v0		# current x coordinate

	li	$v0, 5
	syscall
	move	$t3, $v0		# current y coordinate

beq $s1, 1, exit_func		# Check N = 1

sumloop:
	li	$v0, 5
	syscall
	move	$t4, $v0		# next x coordinate

	li	$v0, 5
	syscall
	move	$t5, $v0		# next y coordinate

	mul $t0, $t3, $t5
	slt $t1, $t0, $zero
	beqz $t1, Else 			# IF y1*y2 >=0, go to Else

	mul $t6, $t3, $t3
	mul $t7, $t5, $t5
	add $t6, $t6, $t7		# t6 = y1^2 + y2 ^2
	sub $t2, $t4, $t2 		# t2 = x2 - x1
	abs $t3, $t3
	abs $t9, $t5
	add $t3, $t3, $t9		# t3 = abs(y1) + abs(-y2)
	
	mtc1.d $t2, $f6
	cvt.d.w $f6, $f6		# f6 = x2 - x1

	mtc1.d $t3, $f8
	cvt.d.w $f8, $f8		# f8 = abs(y1) + abs(y2)

	div.d $f6, $f6, $f8		# f6 = f6 / f8

	mtc1.d $t6, $f8
	cvt.d.w $f8, $f8

	mul.d $f6, $f6, $f8		# t2 = (y1^2 + y2^2)* (x2-x1)

	add.d $f10, $f10, $f6
	j Endif
Else:
	add $t3, $t3, $t5
	sub $t2, $t4, $t2
	mul $t2, $t2, $t3
	abs $t2, $t2
	mtc1.d $t2, $f6
	cvt.d.w $f6, $f6
	add.d $f10, $f10, $f6
	j Endif
Endif:
	# ---------
	# s.d $f10, area
	# li $v0, 3
	# l.d $f12, area
	# syscall
	# -----
	move $t2, $t4			# move next x to current x
	move $t3, $t5			# move next y to current y
	add $s0, $s0, 1
	ble $s0, $s1, sumloop

exit_func:
	div.d $f10, $f10, $f4

	s.d $f10, area

	li	$v0, 4		# print prompt string
	la	$a0, result
	syscall

	li $v0, 3
	l.d $f12, area
	syscall

	li $v0, 10
	syscall
	.end main



