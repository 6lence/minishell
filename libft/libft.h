/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:14:02 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/12 09:26:00 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include "../ft_printf/ft_printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

int		ft_isalpha(int i);
int		ft_isdigit(int i);
int		ft_isalnum(int i);
int		ft_isascii(int i);
int		ft_isprint(int i);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *destination, const void *source, size_t n);
void	*ft_memmove(void *destination, const void *source, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *s, size_t size);
int		ft_toupper(int i);
int		ft_tolower(int i);
char	*ft_strchr(const char *str, int ch);
char	*ft_strrchr(const char *str, int srch);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *str1, const char *str2, size_t n);
int		ft_atoi(char *str);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_memalloc(size_t size);
void	*ft_realloc(void *ptr, size_t size);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_tablen(char **table);

/* gnl */
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*init_string(void);
void	copy_string_contents(char *s1, char *s2);
int		find_line(char *buf, char **line);
char	*free_line(char **line);
char	*ft_count(int fd, char *buf, char *line);

#endif
