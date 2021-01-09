# start of generated code
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
	subq	$8, %rsp
	subq	$8, %rsp
	subq	$8, %rsp
	movq	$1, %rax
	movq	%rax, -88(%rbp)
	subq	$8, %rsp
	movq	$0x3ff199999999999a, %rax
	movq	%rax, -96(%rbp)
	subq	$8, %rsp
	movq	-88(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	-96(%rbp), %xmm1
	ucomisd	%xmm1, %xmm0
	jae	 .POS0
	movq	$0, %rax
	jmp	 .POS1
.POS0:
	movq	$1, %rax
.POS1:
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, -80(%rbp)
	subq	$8, %rsp
	movq	$0x3ff199999999999a, %rax
	movq	%rax, -112(%rbp)
	subq	$8, %rsp
	movq	$1, %rax
	movq	%rax, -120(%rbp)
	subq	$8, %rsp
	movq	-120(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	-112(%rbp), %xmm1
	ucomisd	%xmm0, %xmm1
	jae	 .POS2
	movq	$0, %rax
	jmp	 .POS3
.POS2:
	movq	$1, %rax
.POS3:
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movq	%rax, -80(%rbp)
	subq	$8, %rsp
	movq	$0x3ff199999999999a, %rax
	movq	%rax, -136(%rbp)
	subq	$8, %rsp
	movq	$0x3ff199999999999a, %rax
	movq	%rax, -144(%rbp)
	subq	$8, %rsp
	movq	-136(%rbp), %xmm1
	movq	-144(%rbp), %xmm0
	ucomisd	%xmm0, %xmm1
	jae	 .POS4
	movq	$0, %rax
	jmp	 .POS5
.POS4:
	movq	$1, %rax
.POS5:
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	%rax, -80(%rbp)
	subq	$8, %rsp
	movq	$1, %rax
	movq	%rax, -160(%rbp)
	subq	$8, %rsp
	movq	$1, %rax
	movq	%rax, -168(%rbp)
	subq	$8, %rsp
	movq	-160(%rbp), %rax
	movq	-168(%rbp), %rdx
	cmpq	%rdx, %rax
	jge	 .POS6
	movq	$0, %rax
	jmp	 .POS7
.POS6:
	movq	$1, %rax
.POS7:
	movq	%rax, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -80(%rbp)
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
