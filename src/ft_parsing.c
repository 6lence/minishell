/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:34:37 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/05 11:08:37 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_presence(t_data *l)
{
	t_params	*tmp;

	l->pipe = 0;
	tmp = l->list;
	while (tmp->next)
	{
		if (tmp->str[0] == '|')
			l->pipe = 1;
		tmp = tmp->next;
	}
}

int	ft_params_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_chained_args(t_data *l)
{
	t_params	*new;
	int			i;
	int			params;

	i = 0;
	l->list = NULL;
	params = ft_params_len(l->params_split);
	while (i < params)
	{
		new = malloc(sizeof(t_params));
		if (!new)
			return (1);
		new->str = l->params_split[i];
		new->pos = i;
		new->next = NULL;
		if (l->list)
		{
			new->prev = l->list;
			ft_lstlast(l->list)->next = new;
		}
		else
		{
			new->prev = NULL;
			l->list = new;
		}
		i++;
	}
	return (0);
}

// Function to parse user input and return command and arguments
void	get_command_arguments(const char *input,
			char *command, char **arguments)
{
	char	**tokens;

	tokens = ft_split(input, ' ');
	if (!tokens || !tokens[0])
	{
		command = NULL;
		*arguments = NULL;
		return ;
	}
	command = ft_strjoin(command, tokens[0]);
	*arguments = tokens[1];
}

// Function to execute a command with its arguments
void	execute_command(t_data *l)
{
	pid_t		child_pid;
	int			status;
	char		**arguments;
	int			i;
	t_params	*tmp;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		arguments = ft_calloc(ft_args(l->list), sizeof(char *));
		tmp = l->list;
		i = 0;
		while (arguments[i] && tmp)
		{
			arguments[i] = ft_strjoin(arguments[i], tmp->str);
			tmp = tmp->next;
		}
		execve(l->path, arguments, l->envp);
	}
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		printf("Child process exited with status %d\n", WEXITSTATUS(status));
}
