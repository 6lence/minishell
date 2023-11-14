/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_11.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:56:34 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 09:05:45 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quotes(t_data *l, int *i, int c)
{
	*i = *i + 1;
	while (l->params[*i] != c)
		*i = *i + 1;
}

void	ft_words_2(t_data *l, int *i, int *words)
{
	while (l->params[*i] && !((l->params[*i] < 7
				|| l->params[*i] > 13) && l->params[*i] != ' '))
	{
		if (l->params[*i] == ')' || l->params[*i] == '(')
		{
			*words = *words + 1;
			*i = *i + 1;
		}
		*i = *i + 1;
	}
}

void	ft_words_1(t_data *l, int *i, int *words)
{
	while (l->params[*i] && (l->params[*i] < 7
			|| l->params[*i] > 13) && l->params[*i] != ' ')
	{
		if (l->params[*i] == ')' || l->params[*i] == '(')
		{
			*words = *words + 1;
			*i = *i + 1;
		}
		if (l->params[*i] == 34)
			ft_quotes(l, &*i, 34);
		else if (l->params[*i] == 39)
			ft_quotes(l, &*i, 39);
		*i = *i + 1;
	}
}
