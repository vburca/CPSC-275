/*
 * prime.s: This program computes all primes less than 100.
 *
 * Written by Peter Yoon
 * 10/18/2011
 *
 * Compile with:
 *    gcc -o primes primes.s
 *
 * Run with:
 *    ./primes
 */

.globl main
main:
	pushl	%ebp			# save old frame pointer			
	movl	%esp, %ebp		# set new frame pointer to esp
	subl	$8, %esp		# allocate two local variables
	movl	$100, 4(%esp)		# m: upper bound of the range of the numbers
	movl	$3, (%esp)		# n: number between 3 and 100
.top:
	pushl	-8(%ebp)		# push n 
	call	isprime			# call the function isprime()
	testb	%al, %al		# what was the answer?
	je	.skip			# if the answer was no, don't print
	pushl	-8(%ebp)		# if it is prime, print it
	pushl	$.LC0
	call	printf
.skip:
	incl	-8(%ebp)		# n += 1
	movl	-8(%ebp), %ebx		# copy the value of n to ebx
	cmpl	%ebx, -4(%ebp)		# compare n with m
	jl	.quit			# n > m? if so, we're done
	jmp	.top			# otherwise, continue with the current value of n
.quit:
	leave				# restore ebp and esp, that is,
					#   movl %ebp, %esp
					#   popl %ebp
	ret				# return to the caller

/*
 * This function accepts a number and returns 1 if it is prime; 0 otherwise.
 */
.globl isprime
isprime:
	pushl	%ebp			# save frame pointer
	movl	%esp, %ebp		# set new frame pointer to esp
	movl	$2, %ecx		# denominator d is initialized to 2
.nextnum:
	movl	8(%esp), %eax		# get numerator n in eax
	cltd				# sign extend it
	idivl	%ecx			# n / d
	testl	%edx, %edx		# is remainder 0?
	je	.notprime		# if so, n is not prime
	incl	%ecx			# d += 1
	cmpl	%ecx, 8(%esp)		# is d < n?
	jg	.nextnum		# if so, continue
	movb	$0x01, %al		# otherwise, n is prime; return 1
	jmp 	.done			# ready to return to the caller
.notprime:
	movb	$0x00, %al		# n is not prime; return 0
.done:
	leave				# restore ebp and esp, that is,
	ret				# return to the caller


/* labels used */
.LC0:
	.string "%d\n"
