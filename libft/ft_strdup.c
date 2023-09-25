/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:06:02 by ashalagi          #+#    #+#             */
/*   Updated: 2023/07/18 07:54:49 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc(ft_strlen(src) + 1);
	if (!res)
		return (NULL);
	while (src[i])
	{
		res[i] = src[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
