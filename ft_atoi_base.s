section .text

global ft_atoi_base

; is_whitespace(char, label_to_jump_to_when_true)
%macro is_whitespace 2
	cmp %1, 32 ; == ' '
	je %2

	; [\t \n \v \f \r]
	cmp %1, 9 ; < '\t'
	jl %%_continue

	cmp %1, 13 ; <= '\r'
	jle %2

	%%_continue:
%endmacro

; isnt_whitespace(char, label_to_jump_to_when_true)
%macro isnt_whitespace 2
	cmp %1, 32 ; == ' '
	je %%_continue

	; [\t \n \v \f \r]
	cmp %1, 9 ; < '\t'
	jl %2

	cmp %1, 13 ; > '\r'
	jg %2

	%%_continue:
%endmacro

%macro _ft_atoi_init_map 0
	%assign %%i 0
	%rep 32
		mov qword [map + %%i * 8], 0
		%assign %%i %%i + 1
	%endrep
%endmacro

%define value rax
%define str rdi
%define base rsi
%define base_len rcx
%define base_len_char cl
%define sign rsi

; int ft_atoi_base(char *str: rdi, char *base: rsi) -> value
ft_atoi_base:
	xor value, value ; value = 0

	cmp byte [base], 0
	je _ft_atoi_base_return ; if (*base == '\0') return ;

	xor base_len, base_len ; base_len = 0

	_ft_atoi_init_map

_ft_atoi_base_check_base_loop:
	movzx edx, byte [base] ; get the char

	cmp edx, '+'
	je _ft_atoi_base_return

	cmp edx, '-'
	je _ft_atoi_base_return

	is_whitespace edx, _ft_atoi_base_return

	cmp byte [map + edx], 0 ; check if the char is not in the map
	jne _ft_atoi_base_return

	inc base_len ; put the char_index in the map
	mov byte [map + edx], base_len_char

	inc base ; ++base

	cmp byte [base], 0
	jne _ft_atoi_base_check_base_loop

	cmp base_len, 2; check at least 2 char in base
	jl _ft_atoi_base_return

	mov sign, 1  ; sign = 1

_ft_atoi_base_skip_whitespace:
	isnt_whitespace byte [str], _ft_atoi_base_sign
	inc str
	jmp _ft_atoi_base_skip_whitespace

_ft_atoi_base_sign:
	cmp byte [str], '-'
	je _ft_atoi_base_sign_neg

	cmp byte [str], '+'
	je _ft_atoi_base_sign_pos

_ft_atoi_base_numbers:
	movzx edx, byte [str]
	movzx rdx, byte [map + edx]

	cmp rdx, 0
	je _ft_atoi_base_return_with_sign
	dec rdx

	imul rax, base_len  ; value *= base_len
	add value, rdx       ; value += map[str[i]]

	inc str

	jmp _ft_atoi_base_numbers 

_ft_atoi_base_return_with_sign:
	imul value, sign      ; value *= sign

_ft_atoi_base_return:
	ret

_ft_atoi_base_sign_neg:
	neg sign
_ft_atoi_base_sign_pos:
	inc str
	jmp _ft_atoi_base_sign

section .bss
	map: db 256 dup(?) ; create a unitialized buffer