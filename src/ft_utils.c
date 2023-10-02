/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:33:54 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/02 13:48:47 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	**ft_obtain_command(t_data *l)
{
	t_params	*tmp;
	int			i;

	tmp = l->list;
	i = 0;
	while ()
	while (l->list->next->str[0] != '|')
	{
		
	}
}

// Function to execute a command with its arguments
void	execute_command(t_data *l)
{
	pid_t	child_pid;
	int		status;
	char	**split;
	char	*command;

	child_pid = fork();
	command = ft_obtain_command(l);
	split = ft_obtain_split_arg(l);
	// mettre fonction access ici;
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
		execve(l->path, split, l->envp);
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		printf("Child process exited with status %d\n", WEXITSTATUS(status));
}