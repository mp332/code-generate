# start of generated code
	.data	
	.globl	a
	.align	8
	.type	a, @object
	.size	a, 8
a:
	.long	0
	.globl	b
	.align	8
	.type	b, @object
	.size	b, 8
b:
	.quad	0
	.section		.rodata	
	.text	
	.globl	main
	.type	main, @function
main:
	pushq	 %rbp
	movq	%rsp, %rbp
	pushq	 %rbx
	pushq	 %r10
	pushq	 %r11
	pushq	 %r12
	pushq	 %r13
	pushq	 %r14
	pushq	 %r15
	subq	$8, %rsp
	movq	$1, %rax
	movq	%rax, -64(%rbp)
	subq	$8, %rsp
	movq	a(%rip), %rax
	movq	-64(%rbp), %rdx
	orq	%rax, %rdx
	movq	%rdx, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, a(%rip)
	popq	 %r15
	popq	 %r14
	popq	 %r13
	popq	 %r12
	popq	 %r11
	popq	 %r10
	popq	 %rbx
	leave	
	ret	
	.size	main, .-main

# end of generated code
