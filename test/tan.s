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
	subq	$8, %rsp
	movq	%xmm0, -64(%rbp)
	subq	$8, %rsp
	movq	%xmm1, -72(%rbp)
	subq	$8, %rsp
	movq	%xmm2, -80(%rbp)
	subq	$8, %rsp
	movq	%xmm3, -88(%rbp)
	subq	$8, %rsp
	movq	-64(%rbp), %xmm1
	movq	-80(%rbp), %xmm0
	ucomisd	%xmm0, %xmm1
	je	 .POS2
	movq	$0, %rax
	jmp	 .POS3
.POS2:
	movq	$1, %rax
.POS3:
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	testq	%rax, %rax
	jz	 .POS0
	subq	$8, %rsp
	movq	$0, %rax
	movq	%rax, -104(%rbp)
	movaps	-104(%rbp), %xmm0
	popq	 %r15
	popq	 %r14
	popq	 %r13
	popq	 %r12
	popq	 %r11
	popq	 %r10
	popq	 %rbx
	leave	
	ret	
	jmp	 .POS1
.POS0:
.POS1:
	subq	$8, %rsp
	movsd	-88(%rbp), %xmm4
	movsd	-72(%rbp), %xmm5
	subsd	%xmm5, %xmm4
	movsd	%xmm4, -112(%rbp)
	subq	$8, %rsp
	movsd	-80(%rbp), %xmm4
	movsd	-64(%rbp), %xmm5
	subsd	%xmm5, %xmm4
	movsd	%xmm4, -120(%rbp)
	subq	$8, %rsp
	movsd	-112(%rbp), %xmm4
	movsd	-120(%rbp), %xmm5
	divsd	%xmm5, %xmm4
	movsd	%xmm4, -128(%rbp)
	movaps	-128(%rbp), %xmm0
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
	movq	%rax, -128(%rbp)
	movsd	-64(%rbp), %xmm0
	movsd	-80(%rbp), %xmm1
	movsd	-72(%rbp), %xmm2
	movsd	-88(%rbp), %xmm3
	call	 tan
	subq	$8, %rsp
	movsd	%xmm0, -136(%rbp)
	movq	-128(%rbp), %rdi
	movsd	-136(%rbp), %xmm0
	subq	$8, %rsp
	movl	$1, %eax
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
