/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:53:03 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 22:28:13 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_part_1(t_params *tmp)
{
	t_params	*current;
	char		*status_str;
	int			status;

	current = tmp;
	while (current != NULL)
	{
		assign_operator(current);
		current = current->next;
	}
	if (contains_logical_operators(tmp))
	{
		status = ft_execute_priorities(tmp);
		if (status != 0)
		{
			status_str = ft_itoa(status);
			free(status_str);
		}
		return ;
	}
}

void	ft_parent(t_data *l, pid_t child_pid)
{
	if (l->commands)
		l->child_pid[l->child_pos++] = child_pid;
	if (l->pipe_nb >= 1)
		dup2(l->old_fd[0], 0);
	else
		dup2(l->tmp_in, 0);
	if (l->tmp_in != l->in)
	{
		close(l->tmp_in);
		dup2(l->in, 0);
	}
	close(l->old_fd[0]);
	close(l->old_fd[1]);
	l->pipe_nb--;
}
