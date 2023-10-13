/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_fonct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:30:27 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/21 13:28:09 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*ft_minus(const char *format, t_printf *list)
{
	list->minus = 1;
	while (*format == '-')
		format++;
	if (*format < 58 && *format > 47)
	{
		format = ft_nbr(format, &list->nbr_minus);
		return (format);
	}
	return (format);
}

const char	*ft_point(const char *format, t_printf *list)
{
	list->point = 1;
	while (*format == '.')
		format++;
	if (*format < 58 && *format > 47)
	{
		format = ft_nbr(format, &list->precision);
		return (format);
	}
	return (format);
}

void	ft_hexa_nil(t_printf *list)
{
	if (list->minus)
	{
		ft_putstr_fd("(nil)", 1);
		ft_s_spaces(list, "(nil)");
	}
	else
	{
		ft_s_spaces(list, "(nil)");
		ft_putstr_fd("(nil)", 1);
	}
	list->len += 5;
}

static void	ft_hexa_zero2(t_printf *list)
{
	int	len;
	int	i;

	len = list->precision;
	i = 0;
	while (i < len)
	{
		ft_putchar_fd('0', 1);
		i++;
	}
	list->len += i;
	ft_spaces(list->nbr_minus - len, list);
	return ;
}

void	ft_hexa_zero(t_printf *list, unsigned int n)
{
	int	len;

	if (!n && n != 0)
		return ;
	else if (list->minus && !list->nbr_minus && list->point && !list->precision)
		return ;
	else if (list->point && list->precision && list->minus && list->nbr_minus)
	{
		ft_hexa_zero2(list);
		return ;
	}
	len = ft_hexa_zero_verif(list);
	if (list->minus)
		ft_hexa_zero_minus(len, list);
	else
		ft_hexa_zero_else(len, list);
}
