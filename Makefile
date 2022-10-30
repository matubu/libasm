NAME=libasm.a
SRCS= $(wildcard *.s)
OBJS=$(SRCS:.s=.o)
CFLAGS=-Wall -Wextra -Werror
CFLAGS+=-fsanitize=address -g

all: $(NAME)

%.o: %.s
	nasm -f elf64 $^ -o $@

$(NAME): $(OBJS)
	ar rcs $@ $^

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus: all

test: re
	gcc $(CFLAGS) test.c $(NAME)
	./a.out
	rm -rf a.out

.PHONY: all clean fclean re bonus test
