/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:38:06 by ashalagi          #+#    #+#             */
/*   Updated: 2023/02/16 10:28:40 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *s, size_t size)
{
	size_t	len;
	size_t	i;
	size_t	len_dst;

	if ((!dst || !s) && !size)
		return (0);
	len_dst = ft_strlen(dst);
	if (len_dst >= size)
		return (ft_strlen(s) + size);
	else
	{
		i = 0;
		len = size - len_dst;
		while (*dst)
			++dst;
		while (s[i] && i < len - 1)
		{
			*dst = s[i];
			++dst;
			++i;
		}
		*dst = '\0';
		return (len_dst + ft_strlen(s));
	}
}
