/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:33:54 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/09 15:52:03 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
char	**ft_obtain_command(t_data *l)
{
	t_params	*tmp;
	int			i;
	char		**res;

	
	tmp = l->list;
	i = 0;
	while (l->list->next->str[0] != '|')
	{
		
	}
	return (res);
}
*/

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

char 	**ft_arguments(t_params *l)
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
	i = 1;
	while (i < pos && tmp)
	{
		res[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

// Function to execute a command with its arguments
void	execute_command(t_data *l)
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
		args = ft_arguments(ft_lst_elem(l->list, l->pos));
		args[0] = ft_strdup(l->path);
  		execve(l->path, args, l->envp);
	}
	waitpid(child_pid, 0, 0);
}