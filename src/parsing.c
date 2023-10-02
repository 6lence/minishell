/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:34:37 by mescobar          #+#    #+#             */
/*   Updated: 2023/09/29 13:22:42 by miguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chained_args(t_data *l)
{
	t_params	*new;
	int			i;

	i = 0;
	l->list = NULL;
	while (i++ < ft_lstlen(l))
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
			ft_lstlast(l)->next = new;
		}
		else
		{
			new->prev = NULL;
			l->list = new;
		}
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
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
		execve(l->path, l->arguments, l->envp);
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		printf("Child process exited with status %d\n", WEXITSTATUS(status));
}
