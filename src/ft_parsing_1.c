/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:34:37 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/13 16:02:31 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_presence(t_data *l)
{
	t_params	*tmp;

	l->pipe = 0;
	tmp = l->list;
	l->pipe_nb = 0;
	while (tmp->next)
	{
		if (tmp->str[0] == '|')
		{
			l->pipe_nb++;
			l->pipe = 1;
		}
		tmp = tmp->next;
	}
}

int	ft_params_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_chained_args(t_data *l)
{
	t_params	*new;
	int			i;

	i = 0;
	l->list = NULL;
	while (l->params_split[i++])
	{
		new = malloc(sizeof(t_params));
		if (!new)
			return (1);
		new->str = l->params_split[i];
		new->pos = i;
		new->next = NULL;
		if (l->list)
		{
			new->prev = l->list;
			ft_lstlast(l->list)->next = new;
		}
		else
		{
			new->prev = NULL;
			l->list = new;
		}
	}
	return (0);
}

void	ft_parsing(t_data *l)
{
	l->params_split = ft_calloc(ft_words(l), sizeof(char *));
	ft_fill_split(l);
	if (l->params)
		free(l->params);
	ft_chained_args(l);
}