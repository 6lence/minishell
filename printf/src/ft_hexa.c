/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:50:26 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/21 10:20:54 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printhexa(unsigned int n, char letter, t_printf *list)
{
	if (list->hashtag)
	{
		if (letter == 'X')
			list->len += write(1, "0X", 2);
		else
			list->len += write(1, "0x", 2);
		list->hashtag = 0;
	}
	if (n >= 16)
	{
		ft_printhexa(n / 16, letter, list);
		ft_printhexa(n % 16, letter, list);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd((n + '0'), 1);
		else
		{
			if (letter == 'x')
				ft_putchar_fd((n - 10 + 'a'), 1);
			else
				ft_putchar_fd((n - 10 + 'A'), 1);
		}
	}
}

void	ft_hexa(unsigned int n, t_printf *list, char letter)
{
	if (!n || n == 0)
	{
		ft_hexa_zero(list, n);
		return ;
	}
	ft_hexa_len(n, list);
	if (list->point)
		list->zero = 0;
	if (list->minus)
	{
		if (list->point)
			ft_xx_precision(list, n);
		ft_printhexa(n, letter, list);
		ft_xx_spaces(list, n);
	}
	else
	{
		ft_xx_spaces(list, n);
		if (list->point)
			ft_xx_precision(list, n);
		ft_printhexa(n, letter, list);
	}
}

static void	ft_putadress(unsigned long long n)
{
	if (n >= 16)
	{
		ft_putadress(n / 16);
		ft_putadress(n % 16);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + '0', 1);
		else
			ft_putchar_fd(n - 10 + 'a', 1);
	}
}

static void	ft_len(unsigned long long n, t_printf *list)
{
	while (n != 0)
	{
		n = n / 16;
		list->len += 1;
	}
}

void	ft_hexadress(unsigned long long n, t_printf *list)
{
	if (n == 0)
	{
		ft_hexa_nil(list);
		return ;
	}
	list->len += 2;
	if (list->minus)
	{
		ft_putstr_fd("0x", 1);
		ft_putadress(n);
		ft_p_spaces(list, n);
	}
	else
	{
		ft_p_spaces(list, n);
		ft_putstr_fd("0x", 1);
		ft_putadress(n);
	}
	ft_len(n, list);
}
