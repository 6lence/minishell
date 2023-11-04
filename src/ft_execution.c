/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:33:54 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/04 11:34:15 by mescobar         ###   ########.fr       */
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

void	ft_in_out(t_data *l, pid_t child_pid)
{
	if (!child_pid)
	{
		if (l->pipe_nb >= 1)
			dup2(l->old_fd[1], 1);
		else
			dup2(l->tmp_out, 1);
		close(l->old_fd[1]);
		close(l->old_fd[0]);
	}
}

void	ft_child(t_data *l, t_params *tmp)
{
	char	**args;

	l->path = ft_access_verif(l, tmp);
	args = ft_arguments(tmp);
	if (l->path)
		execve(l->path, args, l->envp);
	printf("Command %s: not found\n", tmp->str);
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
	if (l->pipe_nb >= 1)
		dup2(l->old_fd[0], 0);
	else
		dup2(l->tmp_in, 0);
	close(l->old_fd[0]);
	close(l->old_fd[1]);
	l->pipe_nb--;
}

void	execute_command(t_data *l, t_params *tmp)
{
	pid_t	child_pid;
	int		ct;

	if (pipe(l->old_fd) < 0)
		return (perror("error: fatal\n"));
	ct = is_builtin(tmp->str);
	if (ct)
		return (ft_exec_builtin(l, tmp));
	child_pid = fork();
	ft_in_out(l, child_pid);
	if (!child_pid)
		ft_child(l, tmp);
	else
	{
		l->child_pid[l->child_pos++] = child_pid;
		if (l->pipe_nb >= 1)
			dup2(l->old_fd[0], 0);
		else
			dup2(l->tmp_in, 0);
		close(l->old_fd[0]);
		close(l->old_fd[1]);
		l->pipe_nb--;
	}
}

/*
// Function to execute a command with its arguments
void	execute_command(t_data *l, t_params *tmp)
{
	pid_t		child_pid;
	char		**args;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (ft_access_verif(l, tmp) < 0 && tmp->str != NULL)
		{
			dup2(l->out, 1);
			ft_printf("Command '%s' not found.\n",
				 tmp->str);
				return ;
		}
		args = ft_arguments(tmp);
		execve(l->path, args, l->envp);
	}
	wait(NULL);
}
*/