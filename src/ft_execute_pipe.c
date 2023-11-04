/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:07:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/04 11:44:58 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_data *l)
{
	t_params	*tmp;

	l->pos = 0;
	tmp = l->list;
	l->tmp_in = l->in;
	l->tmp_out = l->out;
	while (tmp)
	{
		ft_look_in_out_put(tmp, l);
		if (ft_look_pipe(&tmp, l) == 0)
		{
			execute_command(l, tmp);
			while (tmp && !(ft_strcmp(tmp->str, "|") == 0))
				tmp = tmp->next;
		}
	}
}
