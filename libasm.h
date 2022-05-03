#ifndef LIBASM_H
# define LIBASM_H

#include <stddef.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, char *src);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_write(int fd, const void *buf, size_t len);

#endif