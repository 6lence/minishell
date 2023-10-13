/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:52:47 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/22 12:27:20 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "limits.h"

void	ft_d(int d, t_printf *list)
{
	char	*nbr;

	if (!d || d == 0)
		return (ft_hexa_zero(list, d));
	if (list->space && d > 0)
		list->len += write(1, " ", 1);
	nbr = ft_itoa(d);
	list->len += ft_strlen(nbr);
	if (list->point)
		list->zero = 0;
	if (list->zero && d < 0)
		ft_putchar_fd('-', 1);
	if (list->minus)
		ft_d_minus(nbr, d, list);
	else
		ft_d_else(nbr, d, list);
	free(nbr);
}

void	ft_c(char arg, t_printf *list)
{
	if (list->minus == 1)
	{
		list->len += write(1, &arg, 1);
		ft_c_spaces(list);
	}
	else
	{
		ft_c_spaces(list);
		list->len += write(1, &arg, 1);
	}
}

void	ft_s(char *str, t_printf *list)
{
	int	len;

	if (!str)
		str = "(null)";
	if (str[0] == '\0')
	{
		if (list->minus)
			return (ft_spaces(list->nbr_minus, list));
		else
			return (ft_spaces(list->nbr, list));
	}
	if (list->point == 1)
		len = list->precision;
	else
		len = ft_strlen(str);
	if (list->minus == 1)
	{
		list->len += ft_putstr_len(str, len, list);
		ft_s_spaces(list, str);
	}
	else
	{
		ft_s_spaces(list, str);
		list->len += ft_putstr_len(str, len, list);
	}
}

void	ft_u(unsigned int d, t_printf *list)
{
	char	*nbr;

	if (!d || d == 0)
		return (ft_hexa_zero(list, d));
	if (list->space)
		list->len += write(1, " ", 1);
	nbr = ft_utioa(d);
	list->len += ft_strlen(nbr);
	if (list->point)
		list->zero = 0;
	if (list->minus)
		ft_u_minus(nbr, d, list);
	else
		ft_u_else(nbr, d, list);
	free(nbr);
}
