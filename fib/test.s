	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_main                   ## -- Begin function main
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$40016, %rsp            ## imm = 0x9C50
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	jmp	LBB0_1
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	%eax, -40016(%rbp,%rax,2)
	addq	$2, %rax
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$20000, %rax            ## imm = 0x4E20
	jne	LBB0_4
## %bb.2:
	movl	-40016(%rbp), %esi
	leaq	L_.str(%rip), %rdi
	xorl	%eax, %eax
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	cmpq	-8(%rbp), %rax
	jne	LBB0_5
## %bb.3:
	xorl	%eax, %eax
	addq	$40016, %rsp            ## imm = 0x9C50
	popq	%rbp
	retq
LBB0_5:
	callq	___stack_chk_fail
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d\n"


.subsections_via_symbols
