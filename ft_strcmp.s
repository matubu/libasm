section .text

global _ft_strcmp

;;;;; int ft_strcmp(char *s1: rdi, char *s2: rsi) -> rax
_ft_strcmp:
	cmp byte [rdi], 0          ; compare *s1 with \0
	je _ft_strcmp_return       ; jump if condition is true

	mov cl, [rdi]              ; save *s1 in cl
	cmp byte [rsi], cl         ; compare cl with *s2
	jne _ft_strcmp_return      ; jump if condition is false

	inc rdi                    ; increment dst
	inc rsi                    ; increment src

	jmp _ft_strcmp             ; jump back

_ft_strcmp_return:
	mov rax, [rdi]
	sub rax, [rsi]
	ret