/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:26:34 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 17:48:43 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chevron_cmp(t_params *params)
{
	if (ft_strcmp(params->str, ">>") == 0
		|| ft_strcmp(params->str, ">") == 0
		|| ft_strcmp(params->str, "<<") == 0
		|| ft_strcmp(params->str, "<") == 0)
		return (1);
	return (0);
}

void	ft_increment(t_params **t)
{
	char	*ct;

	ct = (*t)->str;
	while ((*t))
	{
		if (ft_operator_cmp((*t)) && ft_strcmp((*t)->str, ct))
			break ;
		(*t) = (*t)->next;
	}
}

int	ft_big_execute(t_data *l)
{
	t_params	*tmp;

	l->tmp_in = l->in;
	l->tmp_out = l->out;
	if (l->pipe == 1)
		ft_pipe(l);
	else
	{
		l->pos = 0;
		tmp = l->list;
		while (tmp)
		{
			ft_look_in(tmp, l);
			ft_look_out_put(tmp, l);
			if (l->tmp_in < 0 || l->tmp_out < 0)
			{
				l->tmp_in = l->in;
				l->tmp_out = l->out;
				break ;
			}
			if (ft_chevron_cmp(tmp))
				ft_increment(&tmp);
			if (tmp && ft_operator_cmp(tmp))
				tmp = tmp->next;
			if (tmp)
				execute_command(l, tmp);
			while (tmp && !ft_operator_cmp(tmp))
				tmp = tmp->next;
			if (tmp && ft_chevron_cmp(tmp))
				ft_increment(&tmp);
		}
	}
	return (0);
}

//malloc ok in this function.
int	init(t_data *l)
{
	l->params = readline("minishell-> ");
	if (!l->params)
		return (-1); // Ctrl+D was pressed, return a special code indicating EOF
	if (ft_only_spaces(l->params))
	{
		free(l->params);
		return (1);
	}
	add_history(l->params);
	ft_parsing(l);
	if (!l->list || !l->list->str || !l->list->str[0])
	{
		free(l->params);
		return (0);
	}
	if (ft_lst_elem(l->list, 0))
		l->dir = opendir(ft_lst_elem(l->list, 0)->str);
	ft_pipe_presence(l);
	l->commands = ft_count_command(l);
	l->child_pos = 0;
	l->child_pid = ft_calloc(l->commands, sizeof(int));
	return (0);
}

void	main_loop(t_data *l)
{
	int init_status;

	printf("\033[1;32mWelcome to minishell\033[0m\n");
	while (l->stop_main)
	{
		init_status = init(l);
		if (init_status == -1)
		{
			printf("Exiting...\n"); // Ctrl+D was pressed
//			free ??
			exit (0);
		}
		else if (init_status != 0)
			continue ;
		ft_big_execute(l);
		ft_childs(l);
		ft_free_all(l);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data				*l;
//	struct sigaction	sa;

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
	// sigemptyset(&sa.sa_mask);
	// sa.sa_sigaction = signal_handling;
	// sa.sa_flags = SA_SIGINFO | SA_RESTART;
	// sigaction(SIGINT, &s, 0);
	// sigaction(SIGQUIT, &s, 0);
	setup_signal_handlers();
	main_loop(l);
	rl_clear_history();
	close(l->in);
	close(l->out);
	free(l);
	return (0);
}

/*
//malloc ok in this function.
int	init(t_data *l)
{
	l->params = readline("minishell-> ");
	if (!l->params || ft_only_spaces(l->params))
		return (1);
	add_history(l->params);
	ft_parsing(l);
	if (!l->list || !l->list->str || !l->list->str[0])
		return (0);
	if (ft_lst_elem(l->list, 0))
		l->dir = opendir(ft_lst_elem(l->list, 0)->str);
	ft_pipe_presence(l);
	l->commands = ft_count_command(l);
	l->child_pos = 0;
	l->child_pid = ft_calloc(l->commands, sizeof(int));
	return (0);
}

void	main_loop(t_data *l)
{
	printf("\033[1;32mWelcome to minishell\033[0m\n");
	while (l->stop_main)
	{
		if (init(l) != 0)
			continue ;
		ft_big_execute(l);
		ft_childs(l);
		ft_free_all(l);
	}
}
*/