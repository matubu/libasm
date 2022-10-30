section .text

global ft_list_size

; int ft_list_size(t_list *begin_list: rdi) -> rax
ft_list_size:
	xor rax, rax     ; size = 0

_ft_list_size_loop:
	test rdi, rdi    ; rdi & rdi
	jz _ft_list_size_return

	mov rdi, [rdi+8] ; rdi = rdi->next
	inc rax          ; ++size

	jmp _ft_list_size_loop

_ft_list_size_return:
	ret