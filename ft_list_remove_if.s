section .text

global ft_list_remove_if

extern free

; t_list *curr
%define curr rcx
; t_list **prev
%define prev rdx
; t_list *next
%define next rax

; void	ft_list_remove_if(t_list **begin_list: rdi,
;		void *data_ref: rsi, int (*cmp)(): rdx,
;		void (*free_fct)(void *): rcx);
ft_list_remove_if:
	sub rsp, 8 * 6

	test rdi, rdi ; check if begin_list is null
	jz _ft_list_remove_if_return
	test rdx, rdx ; check if cmp is null
	jz _ft_list_remove_if_return
	test rcx, rcx ; check if free_fct 
	jz _ft_list_remove_if_return

	mov [rsp], rsi    ; data_ref
	mov [rsp+ 8], rdx ; cmp
	mov [rsp+16], rcx ; free_fct

	mov curr, [rdi]
	mov prev, rdi

_ft_list_remove_if_loop:
	test curr, curr
	jz _ft_list_remove_if_return

	mov [rsp+24], curr
	mov [rsp+32], prev

	mov rdi, [curr] ; curr->data
	mov rsi, [rsp] ; data_ref
	call [rsp+8] ; cmp
	test rax, rax
	jz _ft_list_remove_if_remove_node

	mov curr, [rsp+24]
	mov prev, curr
	add prev, 8
	mov curr, [curr+8]
	jmp _ft_list_remove_if_loop

_ft_list_remove_if_return:
	add rsp, 8 * 6
	ret

_ft_list_remove_if_remove_node:
	mov curr, [rsp+24]
	mov prev, [rsp+32]

	mov next, [curr+8] ; next
	mov [prev], next

	mov [rsp+24], next ; save the new curr
	mov [rsp+40], curr

	mov rdi, [curr] ; curr->data
	call [rsp+16] ; free_fct

	mov rdi, [rsp+40]
	call free

	mov curr, [rsp+24]
	mov prev, [rsp+32]

	jmp _ft_list_remove_if_loop