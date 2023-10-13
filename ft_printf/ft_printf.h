/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:41:19 by mescobar          #+#    #+#             */
/*   Updated: 2023/09/03 17:21:49 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "./src/libft/libft.h"
# include <stdio.h>

typedef struct s_printf
{
	int			len;
	int			width;
	int			minus;
	int			zero;
	int			point;
	long long	precision;
	int			hashtag;
	int			space;
	int			plus;
	long long	nbr;
	long long	nbr_minus;
	char		*ben;
}				t_printf;

int			ft_printf(const char *format, ...);
void		ft_char(char arg, t_printf *list);
char		*ft_strchr(const char *s, int c);
void		ft_hexa(unsigned int d, t_printf *list, char letter);
void		ft_hexadress(unsigned long long n, t_printf *list);
void		ft_putnbr(int n);
void		ft_putnbr_un(unsigned int n);
void		ft_putstr_fd(char *str, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_d(int d, t_printf *list);
void		ft_c(char arg, t_printf *list);
void		ft_s(char *str, t_printf *list);
void		ft_u(unsigned int d, t_printf *list);
void		ft_print10(long int d);
char		*ft_itoa(int n);
void		ft_c_spaces(t_printf *list);
void		ft_s_spaces(t_printf *list, char *str);
const char	*ft_flags(const char *format, t_printf *list);
const char	*ft_nbr(const char *format, long long *nb);
void		ft_ini(t_printf *list);
int			ft_putstr_len(const char *str, int len, t_printf *list);
int			ft_in(const char *format, t_printf *list);
const char	*ft_minus(const char *format, t_printf *list);
const char	*ft_point(const char *format, t_printf *list);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_p_spaces(t_printf *list, unsigned long long n);
void		ft_hexa_nil(t_printf *list);
void		ft_spaces(long long diff, t_printf *list);
void		ft_hexa_zero(t_printf *list, unsigned int n);
void		ft_xx_spaces(t_printf *list, unsigned long long n);
void		ft_xx_precision(t_printf *list, unsigned long long n);
void		ft_hexa_len(unsigned long long n, t_printf *list);
void		ft_d_spaces(char *nbr, t_printf *list);
void		ft_d_zero(t_printf *list);
void		ft_d_precision(int d, t_printf *list);
int			ft_max(long long d1, long long d2);
const char	*ft_flags_verif(const char *format, t_printf *list);
int			ft_hexa_zero_verif(t_printf *list);
void		ft_hexa_zero_print(int len, t_printf *list);
void		ft_hexa_zero_minus(int len, t_printf *list);
void		ft_hexa_zero_else(int len, t_printf *list);
void		ft_d_minus(char *nbr, int d, t_printf *list);
void		ft_d_else(char *nbr, int d, t_printf *list);
void		ft_u_minus(char *nbr, unsigned int d, t_printf *list);
void		ft_u_else(char *nbr, unsigned int d, t_printf *list);
char		*ft_utioa(unsigned int d);
void		ft_u_precision(unsigned int d, t_printf *list);
void		ft_s_null(t_printf *list);

#endif
