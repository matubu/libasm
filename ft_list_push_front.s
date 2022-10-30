section .text

global ft_list_push_front

extern malloc

; void ft_list_push_front(t_list **begin_list: rdi, void *data: rsi)
ft_list_push_front:
	push rdi
	push rsi

	mov rdi, 16
	call malloc
	test rax, rax   ; rax & rax
	jz _ft_list_push_front_return

	pop qword [rax]
	pop rdi

	mov rsi, [rdi]
	mov [rax+8], rsi ; new->next = *begin_list

	mov [rdi], rax  ; *begin_list = new

	ret

_ft_list_push_front_return:
	ret