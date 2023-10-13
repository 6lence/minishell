/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:23:02 by mescobar          #+#    #+#             */
/*   Updated: 2023/02/09 13:25:27 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	index;
	size_t	total;

	if (size == 0 && (!dest || !src))
		return (0);
	i = 0;
	while (dest[i] && i < size)
		i++;
	if (size == i)
		return (i + ft_strlen(src));
	if (size < i)
		return (size + ft_strlen(src));
	total = ft_strlen(dest) + ft_strlen(src);
	index = 0;
	while (i < (size - 1) && src[index])
	{
		dest[i] = src[index];
		i++;
		index++;
	}
	dest[i] = '\0';
	return (total);
}
