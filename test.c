#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>
#include "libasm.h"

#define RED "\033[91m"
#define GREEN "\033[92m"
#define ORANGE "\033[33m"
#define RESET "\033[0m"
#define ENDL RESET "\n"

#define BG_RED "\033[101;30m"
#define BG_GREEN "\033[102;30m"

#define ERROR RED "Error " RESET
#define PASS BG_GREEN " PASS " RESET
#define FAIL BG_RED " FAIL " RESET

int fails = 0;

// test
#define test(cond) { \
	int passed = cond; \
	printf(passed ? PASS : FAIL); \
	if (!passed) ++fails; \
}
// printf
#define _f(...) printf(__VA_ARGS__);
// Print a string
void _put_s(const char *s) {
	if (!s) {
		printf(ORANGE "NULL" RESET);
		return ;
	}
	printf(GREEN "\"");
	while (*s) {
		switch (*s)
		{
		case '\t': printf(RED "\\t" GREEN); break;
		case '\n': printf(RED "\\n" GREEN); break;
		case '\v': printf(RED "\\v" GREEN); break;
		case '\f': printf(RED "\\f" GREEN); break;
		case '\r': printf(RED "\\r" GREEN); break;
		default:
			if (isprint(*s))
				putchar(*s);
			else
				printf(RED "\\x%02x" GREEN, *s);
		break;
		}
		++s;
	}
	printf("\"" RESET);
}
#define _s(s) _put_s(s);
// Print ints
#define _lu(n) printf(ORANGE "%lu" RESET, n);
#define _d(n) printf(ORANGE "%d" RESET, n);
#define _ld(n) printf(ORANGE "%ld" RESET, n);

#define _sep printf(", ");

#define _arg(...) _f(" (") __VA_ARGS__ _f(") =>")
#define _ft(...) _f(" ft: (") __VA_ARGS__ _f(")")
#define _std(...) _f(" std: (") __VA_ARGS__ _f(")\n")

void	test_strlen(char *s)
{
	const size_t	ftlen = ft_strlen(s);
	const size_t	stdlen = strlen(s);

	test(ftlen == stdlen);
	_arg(_s(s))
	_ft(_lu(ftlen))
	_std(_lu(stdlen))
}

void	test_strcpy(char *src)
{
	char		ftdst[100];
	char		stddst[100];

	const char	*ftcpy = ft_strcpy(ftdst, src);
	const char	*stdcpy = strcpy(stddst, src);

	test(ftcpy == ftdst && !strcmp(ftdst, stddst));
	_arg(_s(src))
	_ft(_s(ftcpy))
	_std(_s(stdcpy))
}

void	test_strcmp(char *s1, char *s2)
{
	const int	ftcmp = ft_strcmp(s1, s2);
	const int	stdcmp = strcmp(s1, s2);

	test(ftcmp == stdcmp
		|| (ftcmp < 0 && stdcmp < 0)
		|| (ftcmp > 0 && stdcmp > 0));
	_arg(_s(s1) _sep _s(s2))
	_ft(_d(ftcmp))
	_std(_d(stdcmp))
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

void	test_write(t_pipes pipes, const char *buf, size_t len)
{
	errno = 0;
	const ssize_t	ftwrite = ft_write(pipes.ft[1], buf, len);
	int				fterrno = errno;
	char			ftwritten[len + 1];
	ssize_t			ftread = read(pipes.ft[0], ftwritten, len);
	ftwritten[ftread < 0 ? 0 : ftread] = 0;

	errno = 0;
	const ssize_t	stdwrite = write(pipes.std[1], buf, len);
	int				stderrno = errno;
	char			stdwritten[len + 1];
	ssize_t			stdread = read(pipes.std[0], stdwritten, len);
	stdwritten[stdread < 0 ? 0 : stdread] = 0;

	test(ftwrite == stdwrite && fterrno == stderrno
		&& (ftwrite == -1 || !strncmp(ftwritten, stdwritten, len)));
	_arg(_s(buf) _sep _lu(len))
	_ft(_s(ftwritten) _sep _ld(ftwrite) _sep _d(fterrno))
	_std(_s(stdwritten) _sep _ld(stdwrite) _sep _d(stderrno))
}

void	test_read(t_pipes pipes, const char *buf, size_t len)
{
	write(pipes.ft[1], buf, len);
	char			ftwritten[len + 1];
	errno = 0;
	ssize_t			ftread = ft_read(pipes.ft[0], ftwritten, len);
	int				fterrno = errno;
	ftwritten[ftread < 0 ? 0 : ftread] = 0;

	write(pipes.std[1], buf, len);
	char			stdwritten[len + 1];
	errno = 0;
	ssize_t			stdread = read(pipes.std[0], stdwritten, len);
	int				stderrno = errno;
	stdwritten[stdread < 0 ? 0 : stdread] = 0;

	test(ftread == stdread && fterrno == stderrno
		&& (ftread == -1 || !strncmp(ftwritten, stdwritten, len)));
	_arg(_s(buf) _sep _lu(len))
	_ft(_s(ftwritten) _sep _ld(ftread) _sep _d(fterrno))
	_std(_s(stdwritten) _sep _ld(stdread) _sep _d(stderrno))
}

void	test_strdup(char *s) {
	char	*ft = ft_strdup(s);
	char	*std = strdup(s);

	test(ft != NULL && std != NULL && !strcmp(ft, std));
	_arg(_s(s))
	_ft(_s(ft))
	_std(_s(std))

	free(ft);
	free(std);
}

void	test_atoibase(char *s, char *base, int std) {
	int	val = ft_atoi_base(s, base);

	test(val == std);
	_arg(_s(s) _sep _s(base));
	_ft(_d(val))
	_std(_d(std))
}

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
	test_strcmp("abc", "abcz");
	test_strcmp("", "");
	test_strcmp("\0a", "\0b");

	puts("--- Write ---");
	test_write(pipes(), "Hello world", 11);
	test_write(pipes(), "\0yo", 3);
	test_write(pipes(), "Error fd Hello world", 8);
	test_write(pipes_from(-1), "Error fd Hello world", 8);

	puts("--- Read ---");
	test_read(pipes(), "Hello world", 8);
	test_read(pipes(), "Hello world", 11);
	test_read(pipes_from(-1), "Hello world", 8);

	puts("--- Strdup ---");
	test_strdup("test hello");
	test_strdup("1");
	test_strdup("");
	test_strdup("\0test");

	puts("--- Atoibase ---");
	test_atoibase("7", "ab7c", 2);
	test_atoibase("7", "ab7c+", 0);
	test_atoibase("7", "abc7-", 0);
	test_atoibase("7", " ab7c", 0);
	test_atoibase("7", "ab 7c", 0);
	test_atoibase("7", "ab\t7c", 0);
	test_atoibase("7", "ab\f7c", 0);
	test_atoibase("7", "ab\n7c", 0);
	test_atoibase("7", "ab\r7c", 0);
	test_atoibase("7", "ab\v7c", 0);
	test_atoibase("7", "abc7a", 0);
	test_atoibase("7", "01273", 3);
	test_atoibase("7", "01+273", 0);
	test_atoibase("7", "01-273", 0);
	test_atoibase("7", "11", 0);
	test_atoibase("7", "1", 0);
	test_atoibase("7", "01", 0);
	test_atoibase("7", "013", 0);
	test_atoibase("7", "0123", 0);
	test_atoibase("7", "012345", 0);
	test_atoibase("7", "", 0);
	test_atoibase("7865", "0123456789", 7865);
	test_atoibase("7865", "0123456789abcdef", 0x7865);
	test_atoibase("DEF7865", "0123456789ABCDEF", 0xDEF7865);
	test_atoibase("765", "01234567", 00765);
	test_atoibase("-765", "01234567", -00765);
	test_atoibase("--765", "01234567", 00765);
	test_atoibase("---765", "01234567", -00765);
	test_atoibase("+765", "01234567", 00765);
	test_atoibase("-+-765", "01234567", 00765);
	test_atoibase("+-+765", "01234567", -00765);
	test_atoibase("+-+7658456", "01234567", -00765);
	test_atoibase("+-+765 ", "01234567", -00765);
	test_atoibase("+-+\n765 ", "01234567", 0);
	test_atoibase("+-+\n765 ", NULL, 0);
	test_atoibase(NULL, "01234567", 0);
	test_atoibase(NULL, NULL, 0);

	// puts("--- listPushFront ---");
	// puts("--- listPushSize ---");
	// puts("--- listPushSort ---");
	// puts("--- listPushRemoveIf ---");

	printf("Failed tests: " ORANGE "%d\n" RESET, fails);

	return (!!fails);
}
