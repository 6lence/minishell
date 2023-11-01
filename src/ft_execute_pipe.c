/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:07:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/01 12:00:29 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pipe(t_data *l)
{
	int 		last;
	t_params 	*tmp;
	int 		i;

	l->pos = 0;
	tmp = l->list;
	last = ft_lstlast(l->list)->pos;
	i = 0;
	l->tmp_in = l->in;
	l->tmp_out = l->out;
	while (l->pos < last && tmp)
	{
		ft_look_in_out_put(tmp, l);
		if (ft_look_pipe(&tmp, l) == 0)
		{
			dprintf(2, "%s\n", tmp->str);
			execute_command(l, tmp);
			while (tmp && !(ft_strcmp(tmp->str, "|") == 0))
			{
				l->pos++;
				tmp = tmp->next;
			}
			i++;
		}
	}
}
