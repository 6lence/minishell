/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:26:06 by mescobar          #+#    #+#             */
/*   Updated: 2023/02/09 15:24:47 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*scop;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		scop = (char *)ft_calloc((ft_strlen(s + start) + 1), sizeof(char));
	else
		scop = (char *)ft_calloc(len + 1, sizeof(char));
	if (!scop)
		return (NULL);
	i = (size_t)start;
	j = 0;
	while (j < len && s[i])
	{
		scop[j] = ((char *)s)[i];
		i++;
		j++;
	}
	return (scop);
}
