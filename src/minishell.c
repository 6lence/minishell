/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:26:34 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/13 13:20:45 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_simple_execute(t_data *l)
{
	t_params	*tmp;

	l->pos = 0;
	DEBUG_PRINT(("Entering ft_simple_execute"));
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
		{
			DEBUG_PRINT(("Entering execute_command"));
			execute_command(l, tmp);
		}
		while (tmp && !ft_operator_cmp(tmp))
			tmp = tmp->next;
		if (tmp && ft_operator_cmp(tmp))
			ft_increment(&tmp);
	}
	DEBUG_PRINT(("Exiting ft_simple_execute"));
}

int	ft_big_execute(t_data *l)
{
	DEBUG_PRINT(("Entering ft_big_execute"));
	l->tmp_in = l->in;
	l->tmp_out = l->out;
	DEBUG_PRINT(("Input file descriptor saved as %d, Output file descriptor saved as %d", l->tmp_in, l->tmp_out));
	if (l->pipe == 1)
	{
		DEBUG_PRINT(("Pipe detected, calling ft_pipe"));
		ft_pipe(l);
	}
	else
	{
		DEBUG_PRINT(("No pipe detected, calling ft_simple_execute"));
		ft_simple_execute(l);
	}
	DEBUG_PRINT(("Exiting ft_big_execute"));
	return (0);
}

//malloc ok in this function.
int	init(t_data *l)
{
	DEBUG_PRINT(("Calling readline for input..."));
	l->params = readline("minishell-> ");
	if (!l->params)
	{
		DEBUG_PRINT(("EOF detected - Ctrl+D was pressed."));
		return (-1); // Ctrl+D was pressed, return a special code indicating EOF
	}
	if (ft_only_spaces(l->params))
	{
		free(l->params);
		return (1);
	}
	add_history(l->params);
	DEBUG_PRINT(("Parsing input: %s", l->params));
	ft_parsing(l);
	if (!l->list || !l->list->str || !l->list->str[0])
	{
		free(l->params);
		return (0);
	}
	DEBUG_PRINT(("Checking for commands..."));
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
		DEBUG_PRINT(("Starting a new iteration of the main loop..."));
		init_status = init(l);
		if (init_status == -1)
		{
			DEBUG_PRINT(("Exiting the shell..."));
//			printf("l = %p\n", l);
			printf("Exiting...\n"); // Ctrl+D was pressed
//			ft_clean_up(l);
			break;
//			exit (0);
		}
		else if (init_status != 0)
		{
			DEBUG_PRINT(("Continuing to the next iteration due to init status: %d", init_status));
			continue ;
		}
		DEBUG_PRINT(("Executing commands..."));
		ft_big_execute(l);
		ft_childs(l);
		ft_free_all(l);
		DEBUG_PRINT(("Main loop iteration complete."));
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data				*l;
//	struct sigaction	sa;

	(void)av;
	if (ac > 1)
	{
		DEBUG_PRINT(("minishell does not support arguments."));
		perror("You cannot execute minishell with arguments.");
		exit(EXIT_FAILURE);
	}
	DEBUG_PRINT(("Initializing data structure..."));
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
	DEBUG_PRINT(("Entering main loop..."));
	main_loop(l);
	DEBUG_PRINT(("Cleaning up and exiting..."));
	rl_clear_history();
	close(l->in);
	close(l->out);
	free(l);
	return (0);
}
