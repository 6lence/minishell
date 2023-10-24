/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:07:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/23 09:28:26 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_between(t_data *l, t_params *tmp)
{
	dup2(l->old_fd[0], 0);
	dup2(l->new_fd[1], 1);
	execute_command(l, tmp);
	close(l->new_fd[1]);
	close(l->old_fd[0]);
}


int	ft_child(t_data *l, t_params *tmp, int i, int tours)
{
	if (pipe(l->new_fd) < 0)
	{
		perror("Pipe error: ");
		return (1);
	}
	if (i == 0)
	{
		dup2(l->new_fd[1], 1);
		if (l->input)
			dup2(l->input, 0);
		execute_command(l, tmp);
		close(l->new_fd[1]);
		if (l->input)
			close(l->input);
	}
	else if (tours < l->pipe_nb)
		ft_between(l, tmp);
	else
	{
		dup2(l->old_fd[0], 0);
		dup2(l->out, 1);
		if (l->output)
			dup2(l->output, 1);
		execute_command(l, tmp);
		close(l->old_fd[0]);
		if (l->output)
			close(l->output);
	}
	l->old_fd[0] = l->new_fd[0];
	l->old_fd[1] = l->new_fd[1];
	return (0);
}

void    ft_pipe(t_data *l)
{
	int			last;
	t_params	*tmp;
	int			i;

	l->pos = 0;
	tmp = l->list;
	last = ft_lstlast(l->list)->pos;
	i = 0;
	while (l->pos < last && tmp)
	{
		if (ft_strcmp(tmp->str, "|") == 0)
		{
			l->pos++;
			tmp = tmp->next;
		}
		else
		{
			if (ft_child(l, tmp, l->pos, i) == 1)
				return ;
			while (tmp && tmp->str[0] != '|')
			{
				l->pos++;
				tmp = tmp->next;
			}
			i++;
		}
	}
	dup2(l->in, 0);
	dup2(l->out, 1);	
}
