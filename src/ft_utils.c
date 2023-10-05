/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:33:54 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/05 17:14:25 by mescobar         ###   ########.fr       */
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
	char		**res;
	t_params	*tmp;
	int			pipe;
	int			i;

	tmp = l;
	if (tmp->str && tmp->str[0] == '|' && tmp->next)
		tmp = tmp->next;
	pipe = 0;
	while (tmp->str && tmp->str[0] != '|')
	{
		tmp = tmp->next;
		pipe++;
	}
	res = ft_calloc(pipe, sizeof(char *));
	tmp = l;
	i = 0;
	while (i++ < pipe)
	{
		res[i] = ft_strjoin(res[i], tmp->str);
		tmp = tmp->next;
	}
	return (res);
}

// Function to execute a command with its arguments
void	execute_command(t_data *l)
{
	pid_t		child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
		execve(l->path, 
			ft_arguments(ft_lst_elem(l->list, l->pos)), l->envp);
	waitpid(child_pid, 0, 0);
}