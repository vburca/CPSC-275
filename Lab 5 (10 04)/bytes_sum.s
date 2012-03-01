; Author: Vlad Burca    Alex Zhang
; Date: 10 - 04 - 2011
; File: bytes_sum.s

	.file	"bytes_sum.c"
	.section		.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string "Byte 3 = %#x \nByte 2 = %#x \nByte 1 = %#x \nByte 0 = %#x \nSum = %#x \n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$0x12345678, %eax	
	movl 	$0xFF000000, %ebx
	
	andl    %eax, %ebx
	shrl	$24, %ebx
	movl	%ebx, 4(%esp)
	movl	4(%esp), %ecx
	
	movl	$0xFF0000, %ebx
	andl	%eax, %ebx
	shrl	$16, %ebx
	movl	%ebx, 8(%esp)
	addl	8(%esp), %ecx
	
	movl	$0xFF00, %ebx
   	andl	%eax, %ebx
   	shrl	$8, %ebx 
	movl	%ebx, 12(%esp)
	addl	12(%esp), %ecx
	
	movl	$0xFF, %ebx
	andl	%eax, %ebx
	movl	%ebx, 16(%esp)
	addl	16(%esp), %ecx

	movl	%ecx, 20(%esp)

	movl	$.LC0, (%esp)
	call printf
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
	
