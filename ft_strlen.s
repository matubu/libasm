section .text

global ft_strlen

; https://www.youtube.com/watch?v=WiyUf8u78-w

; size_t ft_strlen(const char *s: rdi) -> rax
ft_strlen:
	xor rax, rax            ; set len to 0

_ft_strlen_loop:
	cmp byte [rdi + rax], 0 ; compare char at len with \0
	je _ft_strlen_return    ; jump if condition is true

	inc rax                 ; increment len

	jmp _ft_strlen_loop     ; loop back

_ft_strlen_return:
	ret
