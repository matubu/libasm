section .text

global ft_list_sort

%define curr rcx
%define next rdx
%define tmp rax
%define begin_list rdi
%define cmp_fn rsi

; void ft_list_sort(t_list **begin_list: rdi, int (*cmp)(): rsi)
ft_list_sort:
	sub rsp, 8 * 4
	mov [rsp], begin_list
	mov [rsp+8], cmp_fn

	test begin_list, begin_list
	jz _ft_list_sort_return ; check if begin_list is not null

	test cmp_fn, cmp_fn
	jz _ft_list_sort_return ; check if cmp is not null

_ft_list_sort_loop:
	mov begin_list, [rsp]
	mov curr, [begin_list] ; save the current node

	test curr, curr
	jz _ft_list_sort_return

_ft_list_sort_it:
	mov next, [curr + 8]

	test next, next
	jz _ft_list_sort_return

	mov [rsp+16], curr
	mov [rsp+24], next

	mov rdi, [curr]
	mov rsi, [next]
	call [rsp+8] ; call the function with the two data as arguments

	cmp eax, 0
	jg _ft_list_swap

	mov curr, [rsp+24] ; save the current as the old next

	jmp _ft_list_sort_it

_ft_list_sort_return:
	add rsp, 8 * 4
	ret

; swap the two data
_ft_list_swap:
	mov rax, [rsp+16]
	mov rcx, [rax]

	mov rdi, [rsp+24]
	mov rdx, [rdi]

	mov [rax], rdx
	mov [rdi], rcx

	jmp _ft_list_sort_loop