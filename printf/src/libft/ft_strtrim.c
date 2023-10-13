/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:34:26 by mescobar          #+#    #+#             */
/*   Updated: 2023/02/13 09:15:49 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_beginning(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		if (s1[i] == s2[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static size_t	ft_end(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (i > 0 && s2[j])
	{
		if (s1[i] == s2[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*chain;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = ft_beginning(s1, set);
	j = ft_end(s1, set);
	len = (len - i) - (len - j) + 1;
	chain = ft_substr(s1, i, j - i + 1);
	if (!chain)
		return (NULL);
	return (chain);
}
