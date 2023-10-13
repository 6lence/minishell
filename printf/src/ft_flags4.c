/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:44:27 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/22 10:36:21 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*ft_flags_verif(const char *format, t_printf *list)
{
	if (*format == '#')
	{
		list->hashtag = 1;
		format++;
	}
	else if (*format == ' ')
	{
		list->space = 1;
		format++;
	}
	else if (*format == '+')
	{
		list->plus = 1;
		format++;
	}
	return (format);
}

int	ft_hexa_zero_verif(t_printf *list)
{
	int	len;

	if (list->point)
	{
		len = list->precision;
		list->zero = 0;
	}
	else
		len = 1;
	if (list->plus)
		list->len += write(1, "+", 1);
	if (list->space)
		list->len += write(1, " ", 1);
	return (len);
}

void	ft_hexa_zero_print(int len, t_printf *list)
{
	if ((list->nbr - len && list->zero))
		ft_putchar_fd('0', 1);
	else if (!(list->nbr - len) && list->zero)
		ft_putchar_fd('0', 1);
	else if ((list->nbr - len) && list->zero)
		ft_putchar_fd(' ', 1);
	else
		ft_putchar_fd('0', 1);
}

void	ft_hexa_zero_minus(int len, t_printf *list)
{
	if (!list->precision && list->point)
		ft_spaces(list->nbr_minus - len, list);
	else
	{
		ft_putchar_fd('0', 1);
		ft_spaces((unsigned long long)(list->nbr_minus - len), list);
		list->len += 1;
	}
}

void	ft_hexa_zero_else(int len, t_printf *list)
{
	int	i;

	ft_spaces(list->nbr - len, list);
	i = 0;
	while (i < len)
	{
		ft_hexa_zero_print(len, list);
		i++;
	}
	list->len += i;
}
