/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:41:19 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/22 11:56:51 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_c_spaces(t_printf *list)
{
	long	len;

	if (list->minus == 1)
		len = list->nbr_minus;
	else
		len = list->nbr;
	ft_spaces(len - 1, list);
}

void	ft_s_spaces(t_printf *list, char *str)
{
	long long	diff;
	long		len;
	int			verif;

	verif = ft_strncmp(str, "(null)", ft_strlen(str));
	if (!verif && list->point)
		return (ft_s_null(list));
	if (list->minus == 1)
		len = list->nbr_minus;
	else
		len = list->nbr;
	if (list->point && !list->precision)
		diff = len;
	else if (list->point)
	{
		if (list->precision > (long)ft_strlen(str))
			diff = len - (long)ft_strlen(str);
		else
			diff = len - list->precision;
	}
	else
		diff = len - (long)ft_strlen(str);
	ft_spaces(diff, list);
}

void	ft_p_spaces(t_printf *list, unsigned long long n)
{
	int	tmp;
	int	len;
	int	diff;

	tmp = 2;
	while (n != 0)
	{
		n = n / 16;
		tmp++;
	}
	if (list->minus)
		len = list->nbr_minus;
	else
		len = list->nbr;
	diff = len - tmp;
	tmp = 0;
	while (tmp < diff)
	{
		if (list->zero)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
		tmp++;
	}
	list->len += tmp;
}

const char	*ft_flags(const char *format, t_printf *list)
{
	while (!(ft_in(format, list)))
	{
		if (*format == '0')
		{
			list->zero = 1;
			format++;
		}
		else if (*format < 58 && *format > 47)
			format = ft_nbr(format, &list->nbr);
		else if (*format == '-')
			format = ft_minus(format, list);
		else if (*format == '.')
			format = ft_point(format, list);
		format = ft_flags_verif(format, list);
	}
	return (format);
}
