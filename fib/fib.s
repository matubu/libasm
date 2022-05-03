section .bss

buf:  resd 10000

section .text

global _op

_op:
	xor ecx, ecx
	mov rax, buf

_op_loop:
	mov dword [rax], ecx
	add rax, 4
	add ecx, 2
	cmp ecx, 20000
	jne _op_loop

_op_return:
	mov rax, buf
	ret