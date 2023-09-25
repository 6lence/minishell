/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:55:33 by ashalagi          #+#    #+#             */
/*   Updated: 2023/02/16 11:09:47 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!str1 || !str2) && !n)
		return (NULL);
	if (!*(char *)str2)
		return ((char *)str1);
	while ((char)str1[i] && n > i)
	{
		j = 0;
		while ((char)str1[i + j] == (char)str2[j] && n > (i + j))
		{
			j++;
			if (!(char)str2[j])
				return ((char *)str1 + i);
		}
		i++;
	}
	return (NULL);
}
