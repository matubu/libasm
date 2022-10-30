section .text

global ft_strdup

extern malloc

extern ft_strlen
extern ft_strcpy

; char *ft_strdup(char *s: rdi) -> rax
ft_strdup:
	push rdi        ; store the pointer

	call ft_strlen  ; get the length of the string in rax

	inc rax
	mov rdi, rax    ; pass the length
	call malloc

	pop rsi

	test rax, rax   ; rax & rax
	jz _ft_strdup_allocation_error

	mov rdi, rax
	call ft_strcpy

	ret

_ft_strdup_allocation_error:
	xor rax, rax
	ret