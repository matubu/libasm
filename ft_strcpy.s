section .text

global ft_strcpy

; char *ft_strcpy(char *dst: rdi, char *src: rsi) -> rax
ft_strcpy:
	mov rax, rdi

_ft_strcpy_loop:
	mov cl, [rsi]           ; copy from *src in cl register
	mov [rdi], cl           ; copy cl register in *dst

	cmp byte [rsi], 0       ; compare *src with \0
	je _ft_strcpy_return    ; jump if condition is true

	inc rdi                 ; increment dst
	inc rsi                 ; increment src

	jmp _ft_strcpy_loop     ; jump back

_ft_strcpy_return:
	ret