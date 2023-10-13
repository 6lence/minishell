/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:44:01 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/21 10:20:17 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_u_spaces(char *nbr, t_printf *list)
{
	unsigned int	max;
	int				len;

	max = ft_max(list->precision, ft_strlen(nbr));
	if (list->minus)
	{
		if (list->precision < (int)ft_strlen(nbr))
			len = list->nbr_minus - (int)ft_strlen(nbr);
		else
			len = list->nbr_minus - list->precision;
	}
	else
		len = list->nbr - max;
	ft_spaces(len, list);
}

void	ft_u_minus(char *nbr, unsigned int d, t_printf *list)
{
	if (list->point)
		ft_u_precision(d, list);
	if (list->plus)
		list->len += write(1, "+", 1);
	ft_putstr_fd(nbr, 1);
	ft_u_spaces(nbr, list);
}

void	ft_u_else(char *nbr, unsigned int d, t_printf *list)
{
	ft_u_spaces(nbr, list);
	if (list->point)
		ft_u_precision(d, list);
	if (list->plus)
		list->len += write(1, "+", 1);
	ft_putstr_fd(nbr, 1);
}
