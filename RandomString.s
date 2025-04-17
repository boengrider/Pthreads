	.file	"RandomString.c"
	.text
	.section	.rodata
.LC0:
	.string	"Stray"
.LC1:
	.string	"Funny"
.LC2:
	.string	"Gigantic"
.LC3:
	.string	"Ruthless"
.LC4:
	.string	"Retarded"
.LC5:
	.string	"Bloated"
.LC6:
	.string	"Rude"
.LC7:
	.string	"Moaning"
.LC8:
	.string	"Average"
.LC9:
	.string	"Overpriced"
.LC10:
	.string	"Dog"
.LC11:
	.string	"Boss"
.LC12:
	.string	"Penis"
.LC13:
	.string	"Businessman"
.LC14:
	.string	"Moron"
.LC15:
	.string	"Stomach"
.LC16:
	.string	"Person"
.LC17:
	.string	"Hypochondriac"
.LC18:
	.string	"Student"
.LC19:
	.string	"Product"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$240, %rsp
	movl	$0, -180(%rbp)
	movl	$0, -184(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, -96(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, -88(%rbp)
	leaq	.LC2(%rip), %rax
	movq	%rax, -80(%rbp)
	leaq	.LC3(%rip), %rax
	movq	%rax, -72(%rbp)
	leaq	.LC4(%rip), %rax
	movq	%rax, -64(%rbp)
	leaq	.LC5(%rip), %rax
	movq	%rax, -56(%rbp)
	leaq	.LC6(%rip), %rax
	movq	%rax, -48(%rbp)
	leaq	.LC7(%rip), %rax
	movq	%rax, -40(%rbp)
	leaq	.LC8(%rip), %rax
	movq	%rax, -32(%rbp)
	leaq	.LC9(%rip), %rax
	movq	%rax, -24(%rbp)
	leaq	.LC10(%rip), %rax
	movq	%rax, -176(%rbp)
	leaq	.LC11(%rip), %rax
	movq	%rax, -168(%rbp)
	leaq	.LC12(%rip), %rax
	movq	%rax, -160(%rbp)
	leaq	.LC13(%rip), %rax
	movq	%rax, -152(%rbp)
	leaq	.LC14(%rip), %rax
	movq	%rax, -144(%rbp)
	leaq	.LC15(%rip), %rax
	movq	%rax, -136(%rbp)
	leaq	.LC16(%rip), %rax
	movq	%rax, -128(%rbp)
	leaq	.LC17(%rip), %rax
	movq	%rax, -120(%rbp)
	leaq	.LC18(%rip), %rax
	movq	%rax, -112(%rbp)
	leaq	.LC19(%rip), %rax
	movq	%rax, -104(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, -240(%rbp)
	leaq	-176(%rbp), %rax
	movq	%rax, -232(%rbp)
	leaq	-180(%rbp), %rax
	movq	%rax, -224(%rbp)
	leaq	-184(%rbp), %rax
	movq	%rax, -216(%rbp)
	leaq	-240(%rbp), %rdx
	leaq	-192(%rbp), %rax
	movq	%rdx, %rcx
	leaq	producer(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movl	%eax, -4(%rbp)
	leaq	-240(%rbp), %rdx
	leaq	-200(%rbp), %rax
	movq	%rdx, %rcx
	leaq	consumer(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movl	%eax, -8(%rbp)
	call	pause@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.type	producer, @function
producer:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movl	$0, %edi
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	movq	-56(%rbp), %rcx
	movq	(%rcx), %rax
	movq	8(%rcx), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	16(%rcx), %rax
	movq	24(%rcx), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
.L4:
	call	rand@PLT
	movl	%eax, %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	sarl	$2, %eax
	movl	%edx, %ecx
	sarl	$31, %ecx
	subl	%ecx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	addl	%eax, %eax
	subl	%eax, %edx
	movl	%edx, -4(%rbp)
	movq	-32(%rbp), %rax
	movl	-4(%rbp), %edx
	movl	%edx, (%rax)
	call	rand@PLT
	movl	%eax, %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	sarl	$2, %eax
	movl	%edx, %ecx
	sarl	$31, %ecx
	subl	%ecx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	addl	%eax, %eax
	subl	%eax, %edx
	movl	%edx, -4(%rbp)
	movq	-24(%rbp), %rax
	movl	-4(%rbp), %edx
	movl	%edx, (%rax)
	movl	$1, %edi
	call	sleep@PLT
	jmp	.L4
	.cfi_endproc
.LFE7:
	.size	producer, .-producer
	.section	.rodata
.LC20:
	.string	"%s %s (%d,%d) (%d)\n"
	.text
	.type	consumer, @function
consumer:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rcx
	movq	(%rcx), %rax
	movq	8(%rcx), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	16(%rcx), %rax
	movq	24(%rcx), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
.L6:
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -8(%rbp)
	movl	line.0(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, line.0(%rip)
	movq	-40(%rbp), %rdx
	movl	-8(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rdx
	movq	(%rdx), %rdx
	movq	-48(%rbp), %rcx
	movl	-4(%rbp), %esi
	movslq	%esi, %rsi
	salq	$3, %rsi
	addq	%rsi, %rcx
	movq	(%rcx), %rsi
	movl	-8(%rbp), %edi
	movl	-4(%rbp), %ecx
	movl	%eax, %r9d
	movl	%edi, %r8d
	leaq	.LC20(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$2, %edi
	call	sleep@PLT
	jmp	.L6
	.cfi_endproc
.LFE8:
	.size	consumer, .-consumer
	.data
	.align 4
	.type	line.0, @object
	.size	line.0, 4
line.0:
	.long	1
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
