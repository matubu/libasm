section .text

global ft_write

; size_t ft_write(int fd: rdi, const void *buf: rsi, size_t len: rdx) -> rax
ft_write:
	mov	rax, 0x2000003   ; write syscall number
	syscall

	; TODO handle error

	ret