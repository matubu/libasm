#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "libasm.h"

#define ERROR "\033[91mError\033[0m "
#define GREEN "\033[92m"
#define ORANGE "\033[33m"
#define RESET "\033[0m"
#define ENDL RESET "\n"

#define BG_RED "\033[101;30m"
#define BG_GREEN "\033[102;30m"

#define PASS BG_GREEN " PASS " RESET
#define FAIL BG_RED " FAIL " RESET

void	test_strlen(char *s)
{
	const size_t	ftlen = ft_strlen(s);
	const size_t	stdlen = strlen(s);

	printf(ftlen == stdlen ? PASS : FAIL);
	printf(" (" GREEN "\"%s\"" RESET ") =>", s);
	printf(" ft: " ORANGE "%lu" RESET, ftlen);
	printf(" std: " ORANGE "%lu" ENDL, stdlen);
}

void	test_strcpy(char *src)
{
	char		ftdst[100];
	char		stddst[100];

	const char	*ftcpy = ft_strcpy(ftdst, src);
	const char	*stdcpy = strcpy(stddst, src);

	printf(ftcpy == ftdst && !strcmp(ftdst, stddst) ? PASS : FAIL);
	printf(" (" GREEN "\"%s\"" RESET ") =>", src);
	printf(" ft: " GREEN "\"%s\"" RESET, ftcpy);
	printf(" std: " GREEN "\"%s\"" ENDL, stdcpy);
}

void	test_strcmp(char *s1, char *s2)
{
	const int	ftcmp = ft_strcmp(s1, s2);
	const int	stdcmp = strcmp(s1, s2);

	printf(ftcmp == stdcmp ? PASS : FAIL);
	printf(" (" GREEN "\"%s\"" RESET ", " GREEN "\"%s\"" RESET ") =>", s1, s2);
	printf(" ft: " ORANGE "%d" RESET, ftcmp);
	printf(" std: " ORANGE "%d" ENDL, stdcmp);
}

typedef struct {
	int ft[2];
	int std[2];
}	t_pipes;

t_pipes	pipes_from(int fd)
{
	return ((t_pipes){{ fd, fd }, { fd, fd }});
}

t_pipes	pipes()
{
	t_pipes pipes;
	if (pipe(pipes.ft) < 0 || pipe(pipes.std) < 0) {
		printf(ERROR "could not create pipes");
		exit(1);
	}
	return (pipes);
}

void	test_write(t_pipes pipes, const void *buf, size_t len)
{
	const ssize_t	ftwrite = ft_write(pipes.ft[1], buf, len);
	char			ftwritten[len];
	printf("write\n");
	read(pipes.ft[0], ftwritten, len);
	printf("read\n");

	const ssize_t	stdwrite = write(pipes.std[1], buf, len);
	char			stdwritten[len];
	read(pipes.std[0], stdwritten, len);

	printf(ftwrite == stdwrite && !strncmp(ftwritten, stdwritten, len)
			? PASS
			: FAIL);
	printf(" ft: \"%.*s\" (%zi)", (int)len, ftwritten, ftwrite);
	printf(" std: \"%.*s\" (%zi)\n", (int)len, stdwritten, stdwrite);

	// check errno
}

// void	test_read()
// {}

int	main(void)
{
	puts("--- Strlen ---");
	test_strlen("Hello world");
	test_strlen("0123456789");
	test_strlen("");

	puts("--- Strcpy ---");
	test_strcpy("Hello world");
	test_strcpy("0123456789");
	test_strcpy("");

	puts("--- Strcmp ---");
	test_strcmp("Hello world", "Hello world");
	test_strcmp("abc", "bac");
	test_strcmp("abc", "aba");
	test_strcmp("", "");
	test_strcmp("\0a", "\0b");

	puts("--- Write ---");
	test_write(pipes(), "Hello world", 11);
	test_write(pipes(), "\0yo", 3);
	test_write(pipes(), "Error fd Hello world", 8);
	test_write(pipes_from(-1), "Error fd Hello world", 8);

	// puts("--- Read ---");
	// test_read(pipes(), "Hello world", 8);
	// test_read(pipes_from(-1), "Hello world", 8);

	return (0);
}
