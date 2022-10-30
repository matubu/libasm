section .text

global ft_strcmp

; int ft_strcmp(const char *s1: rdi, const char *s2: rsi) -> rax
ft_strcmp:
	xor rax, rax

_ft_strcmp_loop:
	mov cl, [rdi]              ; save *s1 in cl
	cmp byte [rsi], cl         ; compare cl with *s2
	jne _ft_strcmp_diff        ; jump if condition is false

	cmp byte [rdi], 0          ; compare *s1 with \0
	je _ft_strcmp_return       ; jump if condition is true

	inc rdi                    ; increment dst
	inc rsi                    ; increment src

	jmp _ft_strcmp_loop        ; jump back

_ft_strcmp_diff:
	mov al, byte [rdi]
	movzx rsi, byte [rsi]

	sub rax, rsi

_ft_strcmp_return:
	ret