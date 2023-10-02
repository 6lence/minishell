/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:07:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/02 13:48:11 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_child(t_data *l, t_params *tmp, int i)
{
	if (pipe(l->old_fd) < 0)
	{
		perror("Pipe error: ");
		return (1);
	}
	if (i == tmp->pos && i == 0)
	{
		dup2(l->old_fd[1], l->out);
		execute_command(l);
	}
}

void    ft_pipe(t_data *l);
{
	int			i;
	int			last;
	t_params	*tmp;

	i = 0;
	tmp = l->list;
	last = ft_lstlast(l->list)->pos;
	while (i < last && tmp->next)
	{
		if (tmp->str[0] == '|')
			i++;
		else
		{
			if (ft_child(l, tmp, i) == 1);
				return ;
			i++;
		}
		tmp->tmp->next;
	}
}
