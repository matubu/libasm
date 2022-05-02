#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libasm.h"

#define GREEN "\033[92m"
#define ORANGE "\033[33m"
#define RESET "\033[0m"

#define BG_RED "\033[101;30m"
#define BG_GREEN "\033[102;30m"

#define PASS BG_GREEN " PASS " RESET
#define FAIL BG_RED " FAIL " RESET

void	test_strlen(char *s)
{
	const unsigned long	ftlen = ft_strlen(s);
	const unsigned long	stdlen = strlen(s);

	printf("%s ft:" ORANGE "%3lu" RESET " std:" ORANGE "%3lu" RESET ", " GREEN "\"%s\"\n" RESET,
		ftlen == stdlen ? PASS : FAIL,
		ftlen,
		stdlen,
		s
	);
}

void	test_strcpy(char *src)
{
	char ftdst[100];
	char stddst[100];

	const char *ftcpy = ft_strcpy(ftdst, src);
	const char *stdcpy = strcpy(stddst, src);

	printf("%s ft: " GREEN "\"%s\"" RESET " std: " GREEN "\"%s\"" RESET ", " GREEN "\"%s\"\n" RESET,
		ftcpy == ftdst && !strcmp(ftdst, stddst) ? PASS : FAIL,
		ftcpy,
		stdcpy,
		src
	);
}

void	test_strcmp(char *s1, char *s2)
{
	const int	ftcmp = ft_strcmp(s1, s2);
	const int	stdcmp = strcmp(s1, s2);

	printf("%s ft:" ORANGE "%3d" RESET " std:" ORANGE "%3d" RESET ", " GREEN "\"%s\"" RESET ", " GREEN "\"%s\"\n" RESET,
		ftcmp == stdcmp ? PASS : FAIL,
		ftcmp,
		stdcmp,
		s1,
		s2
	);
}

int	main()
{
	puts("--- STRLEN ---");
	test_strlen("Hello world");
	test_strlen("0123456789");
	test_strlen("");

	puts("--- STRCPY ---");
	test_strcpy("Hello world");
	test_strcpy("0123456789");
	test_strcpy("");

	puts("--- STRCMP ---");
	test_strcmp("Hello world", "Hello world");
	test_strcmp("abc", "bac");
	test_strcmp("abc", "aba");
	test_strcmp("", "");


	return (0);
}