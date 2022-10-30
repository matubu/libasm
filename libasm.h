#ifndef LIBASM_H
# define LIBASM_H

#include <stddef.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t len);
ssize_t	ft_read(int fd, void *buf, size_t len);
char	*ft_strdup(const char *s);

#endif