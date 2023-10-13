/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:39:09 by mescobar          #+#    #+#             */
/*   Updated: 2023/02/23 10:37:15 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(char const *str, char c)
{
	size_t	count;
	size_t	index;

	if (!str || !str[0])
		return (0);
	count = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			index++;
		else
		{
			count++;
			while (str[index] && str[index] != c)
				index++;
		}
	}
	return (count);
}

static size_t	ft_len(size_t i, char const *str, char c)
{
	size_t	count;

	count = 0;
	while (str[i] && str[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static size_t	ft_position(size_t nb, const char *str, char c)
{
	while (str[nb] && str[nb] == c)
		nb++;
	return (nb);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	k;
	size_t	word_len;
	size_t	word_nb;

	if (!s)
		return (NULL);
	word_nb = ft_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (word_nb + 1));
	if (!tab)
		return (NULL);
	i = ft_position(0, s, c);
	k = 0;
	while (k < word_nb)
	{
		word_len = ft_len(i, s, c);
		tab[k] = ft_substr(s, i, word_len);
		i = ft_position(i + word_len, s, c);
		k++;
	}
	tab[k] = NULL;
	return (tab);
}
