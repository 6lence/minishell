/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:34:37 by miguel            #+#    #+#             */
/*   Updated: 2023/09/25 14:49:01 by miguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to parse user input and return command and arguments
void	get_command_arguments(const char *input,
			char *command, char ***arguments)
{
	char	**tokens;

	tokens = ft_split(input, ' ');
	if (!tokens || !tokens[0])
	{
		command = NULL;
		*arguments = NULL;
		return ;
	}
	command = tokens[0];
	*arguments = &tokens[1];
}

// Function to execute a command with its arguments
void	execute_command(t_data *l)
{
	pid_t	child_pid;
	int		status;
	char	*path;

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		path = ft_strjoin("/usr/bin", l->command);
		if (access(path, 0) == 0)
			execve(path, l->command, l->envp);
		else
		{
			perror("Pathway error ");
			exit(EXIT_FAILURE);
		}
	}
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		printf("Child process exited with status %d\n", WEXITSTATUS(status));
}
