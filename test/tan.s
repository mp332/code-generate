# start of generated code
	.section		.rodata	
.LC0:
	.string	"tan = %f\n"
	.text	
	.globl	tan
	.type	tan, @function
tan:
	pushq	 %rbp
	movq	%rsp, %rbp
	pushq	 %rbx
	pushq	 %r10
	pushq	 %r11
	pushq	 %r12
	pushq	 %r13
	pushq	 %r14
	pushq	 %r15
	popq	 %r15
	popq	 %r14
	popq	 %r13
	popq	 %r12
	popq	 %r11
	popq	 %r10
	popq	 %rbx
	leave	
	ret	
	.size	tan, .-tan
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
	subq	$8, %rsp
	subq	$8, %rsp
	subq	$8, %rsp
	subq	$8, %rsp
	movq	$4615063718147915776, %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, -64(%rbp)
	subq	$8, %rsp
	movq	$4615063718147915776, %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, -80(%rbp)
	subq	$8, %rsp
	movq	$4617878467915022336, %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -72(%rbp)
	subq	$8, %rsp
	movq	$4616752568008179712, %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -88(%rbp)
	subq	$8, %rsp
	movq	$.LC0, %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rdi
	subq	$8, %rsp
	movl	$4, %eax
	call	 printf
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
