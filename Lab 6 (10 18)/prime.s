#	Authors: Vlad Burca	Alex Zhang
#	Date:	18  10  11
#	File:	prime.s

	.file	"prime.s"
	.section		.rodata.str1.1,"aMS",@progbits,1

.LC0:
	.string "%d\n"
	.text

.global isprime
	.type	isprime, @function
isprime:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	$2, %ebx
	cmpl	$1, %eax
	je		.L1
	movl	%eax, %ecx
.L0:
	cltd	
	idiv	%ebx
	cmpl	%ecx, %ebx
	je		.L3
	cmpl	$0, %edx
	je		.L1
	addl	$1, %ebx
	movl	%ecx, %eax
	jmp		.L0
.L1:
	xorl	%eax, %eax
	jmp		.L4
.L3:
	movl	$1, %eax
.L4:
	popl	%ebp
	ret
	.size	isprime, .-isprime

.global main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$1, 4(%esp)
.L5:
	call	isprime
	cmpl	$0, %eax
	je		.L6
	movl	$.LC0, (%esp)
	call	printf
.L6:
	addl	$1, 4(%esp)
	cmpl	$100, 4(%esp)
	jg		.L7	
	jmp		.L5
.L7:
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4tubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
