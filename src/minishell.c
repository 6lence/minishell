/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:26:34 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/20 15:48:23 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_globale;

void	ft_simple_execute(t_data *l)
{
	t_params	*tmp;

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
		if (ft_operator_cmp(tmp))
			ft_increment(&tmp);
		if (tmp && ft_operator_cmp(tmp))
			tmp = tmp->next;
		if (tmp)
			execute_command(l, tmp);
		while (tmp && !ft_operator_cmp(tmp))
			tmp = tmp->next;
		if (tmp && ft_operator_cmp(tmp))
			ft_increment(&tmp);
	}
}

int	ft_big_execute(t_data *l)
{
	l->tmp_in = l->in;
	l->tmp_out = l->out;
	if (l->pipe == 1)
		ft_pipe(l);
	else
		ft_simple_execute(l);
	return (0);
}

//malloc ok in this function.
int	init(t_data *l)
{
	g_globale = 0;
	l->params = readline("minishell-> ");
	if (!l->params)
		return (-1);
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
	int	init_status;

	printf("\033[1;32mWelcome to minishell\033[0m\n");
	while (l->stop_main)
	{
		init_status = init(l);
		if (init_status == -1)
			exit (0);
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

	(void)av;
	if (ac > 1)
	{
		perror("You cannot execute minishell with arguments.");
		exit(EXIT_FAILURE);
	}
	l = ft_calloc(sizeof(t_data), 1);
	l->envp = strrdup(envp);
	l->exp_var = 0;
	l->stop_main = 1;
	l->in = dup(STDIN_FILENO);
	l->out = dup(STDOUT_FILENO);
	setup_signal_handlers();
	main_loop(l);
	rl_clear_history();
	close(l->in);
	close(l->out);
	ft_free_split(l->envp, ft_tablen(l->envp));
	free(l);
	return (0);
}

/*
#include <stdio.h>
#include <stdarg.h>

#define DEBUG_PRINT(fmt, ...) do { \
    printf("Debug: "); \
    printf(fmt, ##__VA_ARGS__); \
    printf("\n"); \
} while (0)

*/