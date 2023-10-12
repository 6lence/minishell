/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:33:54 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/12 11:59:22 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

char	**ft_arguments(t_params *l)
{
	t_params	*tmp;
	char		**res;
	int			i;
	int			pos;

	tmp = l;
	i = 0;
	while (tmp && tmp->str[0] != '|')
	{
		i++;
		tmp = tmp->next;
	}
	res = ft_calloc(i + 1, sizeof(char *));
	pos = i;
	tmp = ft_lst_elem(l, 0);
	i = 0;
	while (i < pos && tmp)
	{
		res[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	l->pos += pos;
	res[i] = NULL;
	return (res);
}

// Function to execute a command with its arguments
void	execute_command(t_data *l, t_params *tmp)
{
	pid_t		child_pid;
	int			status;
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
		dprintf(2 ,"%s\n", l->path);
		int	i = 0;
		while (args[i])
			dprintf(2, "%s\n", args[i++]);
		dprintf(2, "\n");
		execve(l->path, args, l->envp);
	}
	waitpid(child_pid, &status, 0);
}
