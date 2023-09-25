/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:59:41 by ashalagi          #+#    #+#             */
/*   Updated: 2023/07/16 15:24:39 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(const char *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static char	*ft_get_word(const char *s, char c)
{
	size_t	word_len;

	if (!ft_strchr(s, c))
		word_len = ft_strlen(s);
	else
		word_len = ft_strchr(s, c) - s;
	return (ft_substr(s, 0, word_len));
}

char	**ft_split(const char *s, char c)
{
	char	**list;
	int		i;

	if (!s)
		return (NULL);
	list = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!s || !list)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			list[i++] = ft_get_word(s, c);
		while (*s != c && *s)
			s++;
	}
	list[i] = NULL;
	return (list);
}
