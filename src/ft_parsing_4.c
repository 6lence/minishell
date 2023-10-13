/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:01:17 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/13 15:38:04 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_spaces(char *str, int *i, int *words)
{
	if (str[*i] == ' ')
	{
		*i++;
		while (str[*i] != ' ')
			*i++;
		*words++;
	}
}

void	ft_double(char *str, int *i, int *words)
{
	if (str[*i] == 39)
	{
		*i++;
		while (str[*i] != 39)
			*i++;
		*words++;
	}
}

void	ft_simple(char *str, int *i, int *words)
{
	if (str[*i] == 34)
	{
		*i++;
		while (str[*i] != 34)
			*i++;
		*words++;
	}
}

int	ft_words(t_data *l)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (l->params[i])
	{
		ft_simple(l->params, &i, &words);
		ft_doubles(l->params, &i, &words);
		ft_spaces(l->params, &i, &words);
		i++;
	}
	return (words);
}
