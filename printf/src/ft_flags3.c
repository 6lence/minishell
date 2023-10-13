/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:02:35 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/21 10:19:49 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hexa_len(unsigned long long n, t_printf *list)
{
	while (n != 0)
	{
		n = n / 16;
		list->len += 1;
	}
}

void	ft_d_precision(int d, t_printf *list)
{
	int	len;
	int	i;

	len = 0;
	if (d < 0)
		ft_putchar_fd('-', 1);
	while (d > 0 || d < 0)
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

void	ft_d_spaces(char *nbr, t_printf *list)
{
	int	len;
	int	max;

	max = ft_max(list->precision + (nbr[0] == '-'), ft_strlen(nbr));
	if (list->minus)
	{
		if (list->precision < (int)ft_strlen(nbr))
			len = list->nbr_minus - (int)ft_strlen(nbr);
		else
			len = list->nbr_minus - list->precision - (nbr[0] == '-');
	}
	else
		len = list->nbr - max;
	ft_spaces(len, list);
}
