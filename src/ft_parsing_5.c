/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:15:56 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/13 15:34:38 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_simple(t_data *l, int *i, int *end, int *k)
{
	if (l->params[*i] == 39)
	{
		*i++;
		while (l->params[*i] != 39)
			*end++;
		l->params_split[*k++] == ft_substr(l->params, *i, *end);
		*i = *end;
	}
}

void	ft_fill_double(t_data *l, int *i, int *end, int *k)
{
	if (l->params[*i] == 34)
	{
		*i++;
		while (l->params[*i] != 34)
			*end++;
		l->params_split[*k++] == ft_substr(l->params, *i, *end);
		*i = *end;
	}
}

void	ft_fill_split(t_data *l)
{
	int	i;
	int	k;
	int	end;

	i = 0;
	end = 0;
	k = 0;
	while (l->params[i])
	{
		while (l->params[i] != 34 || l->params != 39)
		{
			while (l->params[i + end] != ' '
				&& l->params[i + end] != 34 && l->params[i + end] != 39)
				end++;
			l->params_split[k++] = ft_substr(l->params, i, end);
			i = end;
		}
		ft_fill_simple(l, &i, &end, &k);
		ft_fill_double(l, &i, &end, &k);
		while (l->params[i] > 6 && l->params[i] < 14)
			i++;
	}
}
