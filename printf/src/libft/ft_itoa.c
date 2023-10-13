/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:23:50 by mescobar          #+#    #+#             */
/*   Updated: 2023/02/14 09:32:46 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive(int n, char *str)
{
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	if (n <= 9)
		str[ft_strlen(str)] = n + 48;
	else
	{
		ft_recursive(n / 10, str);
		ft_recursive(n % 10, str);
	}
}

char	*ft_itoa(int n)
{
	char	*number;
	int		copy;
	size_t	i;

	i = 0;
	copy = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0 || n < 0)
		i++;
	while (copy != 0)
	{
		copy = copy / 10;
		i++;
	}
	number = (char *)ft_calloc(i + 1, sizeof(char));
	if (!number)
		return (NULL);
	ft_recursive(n, number);
	return (number);
}
