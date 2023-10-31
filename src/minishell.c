/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:26:34 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/31 17:20:05 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_access_verif(t_data *l, t_params *tmp)
{
	int		k;
	int		j;
	char	**path;
	char	*join;
	char	*command;

	path = ft_search_path("PATH", l);
	l->path = NULL;
	command = ft_strjoin("/", tmp->str);
	j = 0;
	k = -1;
	while (path[j])
	{
		join = ft_strjoin(path[j], command);
		if (access(join, 0) == 0)
		{
			l->path = ft_strjoin(path[j], command);
			k = j;
		}
		free(join);
		if (j != k)
			free(path[j]);
		j++;
	}
	if (path)
		free(path);
	if (command)
		free(command);
	return (k);
}

int	ft_big_execute(t_data *l)
{
	t_params	*tmp;

	if (l->pipe == 1)
    {
		ft_pipe(l);
        dup2(l->in, 0);
        dup2(l->out, 1);

    }
	else
	{
		l->pos = 0;
		tmp = l->list;
		while (tmp)
		{
            if (ft_operator_cmp(tmp))
                tmp = tmp->next;
			ft_look_in_out_put(tmp, l);
		    execute_command(l, tmp);
            while (tmp && !ft_operator_cmp(tmp))
                tmp = tmp->next;
		}
	}
	return (0);
}

//malloc ok in this function.
int	init(t_data *l)
{
	l->params = readline("minishell-> ");
	if (!l->params)
		return (1);
	add_history(l->params);
	ft_parsing(l);
	if (!l->list || !l->list->str || !l->list->str[0])
		return (0);
	if (ft_lst_elem(l->list, 0))
		l->dir = opendir(ft_lst_elem(l->list, 0)->str);
	ft_pipe_presence(l);
	l->child_pid = ft_calloc(l->pipe_nb + 1, sizeof(int));
	l->child_pos = 0;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*l;

	(void)av;
	if (ac > 1)
	{
		perror("You cannot execute minishell with arguments.");
		exit(EXIT_FAILURE);
	}
	l = ft_calloc(sizeof(t_data), 1);
	l->envp = envp;
	l->stop_main = 1;
	l->in = dup(STDIN_FILENO);
	l->out = dup(STDOUT_FILENO);
	printf("\033[1;32mWelcome to minishell\033[0m\n");
	while (l->stop_main)
	{
		init(l);
		if (ft_add_var(l) == 0)
			ft_big_execute(l);
		ft_childs(l);
		ft_free_all(l);
	}
	rl_clear_history();
	free(l);
	return (0);
}
