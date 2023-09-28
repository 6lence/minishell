/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:34:37 by miguel            #+#    #+#             */
/*   Updated: 2023/09/28 14:08:11 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
