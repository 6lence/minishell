/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:07:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/10 11:59:47 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verif_in_out(t_data *l)
{
	if (l->tmp_in < 0 || l->tmp_out < 0)
	{
		l->tmp_in = l->in;
		l->tmp_out = l->out;
		return (1);
	}
	return (0);
}

void	ft_pipe(t_data *l)
{
	t_params	*tmp;

	l->pos = 0;
	tmp = l->list;
	while (tmp)
	{
		ft_look_in(tmp, l);
		ft_look_out_put(tmp, l);
		if (ft_verif_in_out(l))
			break ;
		if (tmp && ft_strcmp(tmp->str, "|") && ft_operator_cmp(tmp))
			ft_increment(&tmp);
		if (tmp && ft_look_pipe(&tmp, l) == 0)
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
