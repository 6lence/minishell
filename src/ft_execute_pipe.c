/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:07:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/05 16:56:50 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_between(t_data *l)
{
	dup2(l->old_fd[0], 0);
	dup2(l->new_fd[1], 1);
	execute_command(l);
	close(l->old_fd[0]);
	close(l->new_fd[1]);
}

int	ft_child(t_data *l, t_params *tmp, int i)
{
	if (pipe(l->old_fd) < 0 || pipe(l->new_fd) < 0)
	{
		perror("Pipe error: ");
		return (1);
	}
	if (i == tmp->pos && i == 0)
	{
		dup2(l->old_fd[1], l->out);
		execute_command(l);
		close(l->old_fd[1]);
	}
	else if (i != ft_lstlast(tmp)->pos)
		ft_between(l);
	else
	{
		dup2(l->new_fd[0], 0);
		dup2(STDOUT_FILENO, l->out);
		execute_command(l);
		close(l->new_fd[0]);
	}
	l->new_fd[0] = l->old_fd[0];
	l->new_fd[1] = l->old_fd[1];
	return (0);
}

void    ft_pipe(t_data *l)
{
	int			last;
	t_params	*tmp;

	l->pos = 0;
	tmp = l->list;
	last = ft_lstlast(l->list)->pos;
	while (l->pos < last && tmp->next)
	{
		if (tmp->str[0] == '|')
			l->pos++;
		else
		{
			if (ft_child(l, tmp, l->pos) == 1)
				return ;
			l->pos++;
		}
		tmp = tmp->next;
	}
}
