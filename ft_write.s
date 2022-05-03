section .text

global _ft_write

; size_t ft_write(int fd: rdi, const void *buf: rsi, size_t len: rdx) -> rax
_ft_write:
	mov	rax, 0x2000004   ; write(2)
	syscall

	ret