/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:39:22 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/22 11:48:54 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n)
{
	char	nstr;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}	
	if (n < 0)
	{
		write(1, "-", 1);
		n = n * (-1);
	}
	if (n <= 9)
	{
		nstr = n + 48;
		write(1, &nstr, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void	ft_putnbr_un(unsigned int n)
{
	char	nstr;

	if (n <= 9)
	{
		nstr = n + 48;
		write(1, &nstr, 1);
	}
	else
	{
		ft_putnbr_un(n / 10);
		ft_putnbr_un(n % 10);
	}
}

const char	*ft_nbr(const char *format, long long *nb)
{
	long long	d;

	d = 0;
	while (*format > 47 && *format < 58)
	{
		d = (d * 10) + (*format - '0');
		format++;
	}
	*nb = d;
	return (format);
}

void	ft_s_null( t_printf *list)
{
	if (list->precision < 6)
	{
		if (list->minus)
			ft_spaces(list->nbr_minus, list);
		else
			ft_spaces(list->nbr, list);
	}
	else
	{
		if (list->minus)
			ft_spaces(list->nbr_minus - 6, list);
		else
			ft_spaces(list->nbr - 6, list);
	}
}

int	ft_putstr_len(const char *str, int len, t_printf *list)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "(null)", len) == 0 && list->point == 1 && len < 6)
		return (i);
	while (i < len && str[i])
		ft_putchar_fd(str[i++], 1);
	return (i);
}
