	.file	"thread_create.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Printing parameter passed to the thread: %s\n"
	.text
	.globl	thread_fn_callback
	.type	thread_fn_callback, @function
thread_fn_callback:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	thread_fn_callback, .-thread_fn_callback
	.section	.rodata
	.align 8
.LC1:
	.string	"Error creating a new thread, error code: %d\n"
	.text
	.globl	thread1_create
	.type	thread1_create, @function
thread1_create:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	thread_input1.0(%rip), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rcx
	leaq	thread_fn_callback(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	je	.L5
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	exit@PLT
.L5:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	thread1_create, .-thread1_create
	.section	.rodata
.LC2:
	.string	"Pausing the main thread"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, %eax
	call	thread1_create
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	call	pause@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.section	.rodata
.LC3:
	.string	"I am thread no 1"
	.section	.data.rel.local,"aw"
	.align 8
	.type	thread_input1.0, @object
	.size	thread_input1.0, 8
thread_input1.0:
	.quad	.LC3
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
