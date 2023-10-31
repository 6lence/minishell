/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:13:35 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/31 15:08:38 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_params *l)
{
	t_params	*tmp;

	if (l)
	{
		while (l)
		{
			tmp = l;
			l = l->next;
			tmp->next = NULL;
			free(tmp);
		}
	}
}

void	ft_free_split(char **str, int len)
{
	int	i;

	i = 0;
	while (i < len + 1)
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

void	ft_free_all(t_data *l)
{
	int	i;

	i = ft_lstlast(l->list)->pos;
	if (l->params_split)
		ft_free_split(l->params_split, i);
	if (l->list)
		ft_free_list(l->list);
	if (l->params)
		free(l->params);
	l = NULL;
}