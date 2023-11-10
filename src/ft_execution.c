/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:33:54 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/10 11:27:08 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe_here(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exec_builtin(t_data *l, t_params *tmp)
{
	if (l->pipe_nb >= 1)
		dup2(l->old_fd[1], 1);
	else
		dup2(l->tmp_out, 1);
	close(l->old_fd[1]);
	close(l->old_fd[0]);
	execute_builtin(l, tmp);
	if (l->tmp_out != l->out)
	{
		close(l->tmp_out);
		dup2(l->out, 1);
	}
	ft_free_all(l);
	exit(EXIT_SUCCESS);
}

void	ft_child(t_data *l, t_params *tmp)
{
	char	**args;

	l->path = ft_access_verif(l, tmp);
	if (l->path)
	{
		args = ft_arguments(tmp);
		dprintf(2, "out: %d\n", dup(1));
		execve(l->path, args, l->envp);
	}
	printf("Command %s: not found\n", tmp->str);
}

void	ft_in_out(t_data *l)
{
	dprintf(2, "%d\n", l->pipe_nb);
	if (l->pipe_nb >= 1)
		dup2(l->old_fd[1], 1);
	else
	{
		dup2(l->tmp_out, 1);
		dup2(l->tmp_in, 0);
	}
	close(l->old_fd[1]);
	close(l->old_fd[0]);
}

void	execute_command(t_data *l, t_params *tmp)
{
	pid_t		child_pid;
	int			ct;

	if (pipe(l->old_fd) < 0)
		return (perror("error: fatal\n"));
	ft_execute_part_1(tmp);
	ct = is_builtin(tmp->str) && l->tmp_out == l->out;
	if (ct && !l->pipe)
		execute_builtin(l, tmp);
	child_pid = fork();
	if (ct && !child_pid && l->pipe)
		ft_exec_builtin(l, tmp);
	if (!ct && !child_pid)
	{
		ft_in_out(l);
		ft_child(l, tmp);
	}
	else
		ft_parent(l, child_pid);
}
