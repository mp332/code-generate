# start of generated code
	.section		.rodata	
.LC0:
	.string	"b=%f,a=%f"
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
	subq	$8, %rsp
	subq	$8, %rsp
	movq	$1, %rax
	movq	%rax, -80(%rbp)
	subq	$8, %rsp
	movq	$0x4000cccccccccccd, %rax
	movq	%rax, -88(%rbp)
	subq	$8, %rsp
	movq	-80(%rbp), %rbx
	cvtsi2sdq	%rbx, %xmm4
	movsd	-88(%rbp), %xmm5
	subsd	%xmm5, %xmm4
	movsd	%xmm4, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, -72(%rbp)
	subq	$8, %rsp
	movq	$.LC0, %rax
	movq	%rax, -104(%rbp)
	subq	$8, %rsp
	movq	$0x3ff0000000000000, %rax
	movq	%rax, -112(%rbp)
	subq	$8, %rsp
	subq	$8, %rsp
	movq	$0x8000000000000000, %rax
	movq	-112(%rbp), %rdx
	xorq	%rax, %rdx
	movq	%rdx, -120(%rbp)
	movq	-104(%rbp), %rdi
	movsd	-72(%rbp), %xmm0
	movsd	-120(%rbp), %xmm1
	subq	$8, %rsp
	movl	$2, %eax
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
