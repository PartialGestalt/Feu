	.file	"feu_object.c"
	.text
	.type	feu_list_pop, @function
feu_list_pop:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	feu_list_pop, .-feu_list_pop
	.local	feu_object_garbage
	.comm	feu_object_garbage,8,8
	.globl	feu_object_init
	.type	feu_object_init, @function
feu_object_init:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	movq	-8(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 24(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 32(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 40(%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	feu_object_init, .-feu_object_init
	.globl	feu_object_create
	.type	feu_object_create, @function
feu_object_create:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$48, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L6
	movl	$0, %eax
	jmp	.L7
.L6:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	feu_object_init@PLT
	movq	-8(%rbp), %rax
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	feu_object_create, .-feu_object_create
	.section	.rodata
.LC0:
	.string	"Destroying object: \"%s\"\n"
	.align 8
.LC1:
	.string	"Destroying unnamed object @0x%p\n"
	.text
	.globl	feu_object_destroy
	.type	feu_object_destroy, @function
feu_object_destroy:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	cmpq	$0, -56(%rbp)
	je	.L27
.L9:
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L11
	movq	-56(%rbp), %rax
	movq	(%rax), %rdx
	leaq	.LC0(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L13
.L11:
	leaq	.LC1(%rip), %rax
	movq	-56(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L13
.L16:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	feu_object_destroy@PLT
.L13:
	movq	-56(%rbp), %rax
	addq	$40, %rax
	movq	%rax, %rdi
	call	feu_list_pop
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L14
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	subq	$16, %rax
	jmp	.L15
.L14:
	movl	$0, %eax
.L15:
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L16
	jmp	.L17
.L20:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	feu_property_destroy@PLT
.L17:
	movq	-56(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rdi
	call	feu_list_pop
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	je	.L18
	movq	-32(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	subq	$32, %rax
	jmp	.L19
.L18:
	movl	$0, %eax
.L19:
	movq	%rax, -48(%rbp)
	cmpq	$0, -48(%rbp)
	jne	.L20
	movq	-56(%rbp), %rax
	movq	$0, (%rax)
	movq	-56(%rbp), %rax
	movq	%rax, %rdx
	movl	$48, %esi
	movl	$0, %eax
	movq	%rdx, %rcx
	andl	$1, %ecx
	testq	%rcx, %rcx
	je	.L21
	movb	%al, (%rdx)
	addq	$1, %rdx
	subl	$1, %esi
.L21:
	movq	%rdx, %rcx
	andl	$2, %ecx
	testq	%rcx, %rcx
	je	.L22
	movw	%ax, (%rdx)
	addq	$2, %rdx
	subl	$2, %esi
.L22:
	movq	%rdx, %rcx
	andl	$4, %ecx
	testq	%rcx, %rcx
	je	.L23
	movl	%eax, (%rdx)
	addq	$4, %rdx
	subl	$4, %esi
.L23:
	movl	%esi, %ecx
	shrl	$3, %ecx
	movl	%ecx, %ecx
	movq	%rdx, %rdi
	rep stosq
	movq	%rdi, %rdx
	movl	%esi, %ecx
	andl	$4, %ecx
	testl	%ecx, %ecx
	je	.L24
	movl	%eax, (%rdx)
	addq	$4, %rdx
.L24:
	movl	%esi, %ecx
	andl	$2, %ecx
	testl	%ecx, %ecx
	je	.L25
	movw	%ax, (%rdx)
	addq	$2, %rdx
.L25:
	movl	%esi, %ecx
	andl	$1, %ecx
	testl	%ecx, %ecx
	je	.L26
	movb	%al, (%rdx)
	addq	$1, %rdx
.L26:
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	jmp	.L8
.L27:
	nop
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	feu_object_destroy, .-feu_object_destroy
	.globl	feu_property_init
	.type	feu_property_init, @function
feu_property_init:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	movq	-8(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 16(%rax)
	movq	-8(%rbp), %rax
	movl	$0x00000000, %edx
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 32(%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	feu_property_init, .-feu_property_init
	.globl	feu_property_create
	.type	feu_property_create, @function
feu_property_create:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$40, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L30
	movl	$0, %eax
	jmp	.L31
.L30:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	feu_property_init@PLT
	movq	-8(%rbp), %rax
.L31:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	feu_property_create, .-feu_property_create
	.section	.rodata
.LC3:
	.string	"Destroying property: \"%s\"\n"
	.align 8
.LC4:
	.string	"Destroying unnamed property @0x%p\n"
	.text
	.globl	feu_property_destroy
	.type	feu_property_destroy, @function
feu_property_destroy:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L38
.L33:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L35
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	leaq	.LC3(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L36
.L35:
	leaq	.LC4(%rip), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L36:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L37
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
.L37:
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	movq	$0, 8(%rax)
	movq	$0, 16(%rax)
	movq	$0, 24(%rax)
	movq	$0, 32(%rax)
	nop
	jmp	.L32
.L38:
	nop
.L32:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	feu_property_destroy, .-feu_property_destroy
	.ident	"GCC: (GNU) 4.6.3 20120306 (Red Hat 4.6.3-2)"
	.section	.note.GNU-stack,"",@progbits
