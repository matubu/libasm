NAME=libasm.a
SRCS= $(wildcard *.s)
OBJS=$(SRCS:.s=.o)
CFLAGS=-Wall -Wextra -Werror

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

test: re
	gcc $(CFLAGS) test.c $(NAME)
	./a.out
	rm -rf a.out

.PHONY: all clean fclean re test
