section .text

global ft_read

extern __errno_location

; ssize_t ft_read(int fd: rdi, void *buf: rsi, size_t len: rdx) -> rax
ft_read:
	mov	rax, 0            ; read syscall number
	syscall

	cmp rax, 0
	jl _ft_read_error     ; rax is under 0

	ret

_ft_read_error:
	imul rdx, rax, -1     ; save error in rdx

	call __errno_location ; get the address of errno in rax
	mov [rax], rdx

	mov rax, -1           ; return -1

	ret