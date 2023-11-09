/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:07:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 17:03:40 by mescobar         ###   ########.fr       */
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
		if (l->tmp_in < 0 || l->tmp_out < 0)
		{
			l->tmp_in = l->in;
			l->tmp_out = l->out;
			break ;
		}
		if (ft_chevron_cmp(tmp))
			ft_increment(&tmp);
		if (tmp && ft_operator_cmp(tmp))
			tmp = tmp->next;
		if (ft_look_pipe(&tmp, l) == 0)
		{
			execute_command(l, tmp);
			while ((tmp && (!ft_strcmp(tmp->str, "|") == 0
				|| !ft_operator_cmp(tmp))))
				tmp = tmp->next;
		}
		if (tmp && ft_chevron_cmp(tmp))
			ft_increment(&tmp);
	}
}
