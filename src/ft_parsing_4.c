/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:15:56 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/24 10:41:37 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_until_quote(t_data *l, int *i, int *end, int c)
{
	*end = *end + 1;
	while (l->params[*i + *end] != c)
		*end = *end + 1;
}

void	ft_while_spaces(t_data *l, int *i)
{
	while (l->params[*i] && 
			!((l->params[*i] < 7 || l->params[*i] > 13)
			&& l->params[*i] != ' '))
		*i = *i + 1;
}

void	ft_go(t_data *l, int *i, int *end)
{
	*end = 0;
	while (l->params[*i + *end] && 
			(l->params[*i + *end] < 7 || l->params[*i + *end] > 13)
			&& l->params[*i + *end] != ' ')
	{
		if (l->params[*i + *end] == 34)
			ft_until_quote(l, i, end, 34);
		else if (l->params[*i + *end] == 39)
			ft_until_quote(l, i, end, 39);
		*end = *end + 1;
	}
}

void	ft_fill_split(t_data *l)
{
	int	i;
	int	k;
	int	end;

	i = 0;
	k = 0;
	while (l->params[i])
	{
		ft_go(l, &i, &end);
		l->params_split[k++] = ft_substr(l->params, i, end);
		i += end;
		ft_while_spaces(l, &i);
	}
	l->params_split[k] = NULL;
}
