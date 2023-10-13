/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:00:21 by mescobar          #+#    #+#             */
/*   Updated: 2023/03/22 12:30:52 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*ft_search(va_list arg, const char *format, t_printf *list)
{
	format = ft_flags(format, list);
	if (*format == 'd')
		ft_d(va_arg(arg, int), list);
	else if (*format == 'c')
		ft_c(va_arg(arg, int), list);
	else if (*format == 's')
		ft_s(va_arg(arg, char *), list);
	else if (*format == 'p')
		ft_hexadress(va_arg(arg, unsigned long long), list);
	else if (*format == 'i')
		ft_d(va_arg(arg, unsigned int), list);
	else if (*format == 'u')
		ft_u(va_arg(arg, unsigned int), list);
	else if (*format == 'x' || *format == 'X')
		ft_hexa(va_arg(arg, unsigned int), list, *format);
	else if (*format == '%')
		list->len += write(1, "%", 1);
	format++;
	ft_ini(list);
	return (format);
}

static const char	*ft_read(t_printf *list, const char *format)
{
	char	*next;

	next = ft_strchr(format, '%');
	if (next)
		list->width = next - format;
	else
		list->width = ft_strlen(format);
	write(1, format, list->width);
	list->len += list->width;
	while (*format && *format != '%')
		++format;
	return (format);
}

void	ft_ini(t_printf *list)
{
	list->nbr = 0;
	list->nbr_minus = 0;
	list->minus = 0;
	list->zero = 0;
	list->point = 0;
	list->hashtag = 0;
	list->space = 0;
	list->plus = 0;
	list->precision = 0;
	list->ben = "dcspiuxX%";
}

int	ft_printf(const char *format, ...)
{
	va_list		arg;
	t_printf	list;

	va_start(arg, format);
	ft_ini(&list);
	list.len = 0;
	list.width = 0;
	while (*format)
	{
		if (*format == '%')
			format = ft_search(arg, format + 1, &list);
		else
			format = ft_read(&list, format);
		if (!format)
		{
			write(1, "(null)", 6);
			va_end(arg);
			return (list.len);
		}
	}
	va_end(arg);
	return (list.len);
}
