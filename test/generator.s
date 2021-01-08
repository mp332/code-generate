# start of generated code
	.section		.rodata	
.LC0:
	.string	"ind(%lld) = %lld \n"
	.text	
	.globl	ind
	.type	ind, @function
ind:
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
	movq	-80(%rbp), %rax
	movq	%rax, -64(%rbp)
