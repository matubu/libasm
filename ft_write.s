section .text

global ft_write

extern __errno_location

; ssize_t ft_write(int fd: rdi, const void *buf: rsi, size_t len: rdx) -> rax
ft_write:
	mov	rax, 1            ; write syscall number
	syscall

	cmp rax, 0
	jl _ft_write_error    ; rax is under 0

	ret

_ft_write_error:
	imul rdx, rax, -1     ; save error in rdx

	call __errno_location ; get the address of errno in rax
	mov [rax], rdx

	mov rax, -1           ; return -1

	ret