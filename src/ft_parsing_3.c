/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:01:17 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/06 14:22:10 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quotes(t_data *l, int *i, int c)
{
	*i = *i + 1;
	while (l->params[*i] != c)
		*i = *i + 1;
}

int	ft_words(t_data *l)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (l->params[i])
	{
		while (l->params[i] && (l->params[i] < 7 
				|| l->params[i] > 13) && l->params[i] != ' ')
		{
			if (l->params[i] == 34)
				ft_quotes(l, &i, 34);
			else if (l->params[i] == 39)
				ft_quotes(l, &i, 39);
			i++;
		}
		words++;
		while (l->params[i] && !((l->params[i] < 7 
					|| l->params[i] > 13) && l->params[i] != ' '))
			i++;
	}
	return (words);
}

int	ft_operator_cmp(t_params *tmp)
{
	if (ft_strcmp(tmp->str, "<") == 0
		|| ft_strcmp(tmp->str, "<<") == 0
		|| ft_strcmp(tmp->str, ">") == 0
		|| ft_strcmp(tmp->str, ">>") == 0
		|| (ft_strcmp(tmp->str, "|") == 0 && !(ft_strcmp(tmp->str, "||") == 0)))
		return (1);
	return (0);
}
