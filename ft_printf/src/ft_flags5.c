/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:11:51 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/21 10:20:09 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_d_minus(char *nbr, int d, t_printf *list)
{
	int	tmp;

	if (list->point)
		ft_d_precision(d, list);
	if (list->plus && d > 0)
		list->len += write(1, "+", 1);
	tmp = ((d < 0 && list->point) || (list->zero && d < 0));
	ft_putstr_fd(nbr + tmp, 1);
	ft_d_spaces(nbr, list);
}

void	ft_d_else(char *nbr, int d, t_printf *list)
{
	int	tmp;

	ft_d_spaces(nbr, list);
	if (list->point)
		ft_d_precision(d, list);
	if (list->plus && d > 0)
		list->len += write(1, "+", 1);
	tmp = ((d < 0 && list->point) || (list->zero && d < 0));
	ft_putstr_fd(nbr + tmp, 1);
}

static void	ft_recursive(unsigned int d, char *str)
{
	if (d <= 9)
		str[ft_strlen(str)] = d + 48;
	else
	{
		ft_recursive(d / 10, str);
		ft_recursive(d % 10, str);
	}
}

char	*ft_utioa(unsigned int d)
{
	char			*number;
	unsigned int	copy;
	size_t			i;

	i = 0;
	copy = d;
	if (d == 0)
		i++;
	while (copy != 0)
	{
		copy = copy / 10;
		i++;
	}
	number = (char *)calloc(i + 1, sizeof(char));
	if (!number)
		return (NULL);
	ft_recursive(d, number);
	return (number);
}

void	ft_u_precision(unsigned int d, t_printf *list)
{
	int	len;
	int	i;

	len = 0;
	while (d > 0)
	{
		d = d / 10;
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
