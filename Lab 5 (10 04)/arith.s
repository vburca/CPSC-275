	.file	"arith.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"x y z = %d %d %d \n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$30, 12(%esp)
	movl	$20, 8(%esp)
	movl	$10, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
