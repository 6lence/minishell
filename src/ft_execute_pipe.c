/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:07:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 21:46:44 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_data *l)
{
	t_params	*tmp;

	l->pos = 0;
	tmp = l->list;
	while (tmp)
	{
		ft_look_in(tmp, l);
		ft_look_out_put(tmp, l);
		if (ft_look_pipe(&tmp, l) == 0)
		{
			execute_command(l, tmp);
			while ((tmp && (!ft_strcmp(tmp->str, "|") == 0
						|| !ft_operator_cmp(tmp))))
				tmp = tmp->next;
			l->tmp_in = l->in;
			l->tmp_out = l->out;
		}
	}
}
