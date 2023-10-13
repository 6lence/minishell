/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:27:30 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/22 12:32:43 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_in(const char *format, t_printf *list)
{
	int	i;

	i = 0;
	while (list->ben[i])
	{
		if (*format == list->ben[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_max(long long d1, long long d2)
{
	if (d1 > d2)
		return (d1);
	return (d2);
}

void	ft_xx_spaces(t_printf *list, unsigned long long n)
{
	int	tmp;
	int	len;

	tmp = 0;
	while (n > 0)
	{
		n = n / 16;
		tmp++;
	}
	if (list->minus)
	{
		if (list->precision < tmp)
			len = list->nbr_minus - tmp;
		else
			len = list->nbr_minus - list->precision;
	}
	else
		len = list->nbr - ft_max(list->precision, tmp);
	ft_spaces(len, list);
}

void	ft_xx_precision(t_printf *list, unsigned long long n)
{
	int	i;
	int	len;

	if (!n)
		return ;
	len = 0;
	while (n > 0)
	{
		n = n / 16;
		len++;
	}
	len = list->precision - len;
	i = 0;
	while (i < len)
	{
		ft_putchar_fd('0', 1);
		i++;
	}
	list->len += i;
}

void	ft_spaces(long long diff, t_printf *list)
{
	int	i;

	i = 0;
	while (i < diff)
	{
		if (!list->zero)
			ft_putchar_fd(' ', 1);
		else
			ft_putchar_fd('0', 1);
		i++;
	}
	list->len += i;
}
