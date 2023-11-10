/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_priorities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:44:40 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/10 14:59:33 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NONE 0
#define AND 1
#define OR 2
#define ERROR -1
#define MAX_ARGS 64
#define MAX_ARG_LENGTH 256

t_params *create_temp_command_node(char *cmd_str)
{
	t_params	*temp;

	temp = malloc(sizeof(t_params));
	temp->str = ft_strdup(cmd_str);
	temp->operator = NONE;
	temp->next = NULL;
	temp->cmd = NULL;
	temp->args = NULL;
	if (ft_strcmp(cmd_str, "&&") == 0)
		temp->operator = AND;
	else if (ft_strcmp(cmd_str, "||") == 0)
		temp->operator = OR;
	else
		ft_non_operator(cmd_str, temp, MAX_ARGS);
	return (temp);
}

int contains_logical_operators(t_params *tmp)
{
	while (tmp != NULL)
	{
		if (tmp->operator != NONE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int execute_operator(t_params *cmd)
{
	pid_t pid;
	int status;

	if (cmd->cmd == NULL)
	{
		fprintf(stderr, "Null command encountered.\n");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		execvp(cmd->cmd, cmd->args);
		perror("execvp error");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = EXIT_FAILURE;
	}
	return status;
}

int ft_execute_priorities(t_params *commands)
{
	int			status;
	t_params	*current;
	char		*cmd_str;

	current = commands;
	cmd_str = NULL;
	status = 0;
	while (current != NULL)
	{
		if (current->operator == NONE)
			ft_current_operator_none(&current, &status, cmd_str);
		else if (current->operator == AND)
			ft_current_operator_and(&current, status);
		else if (current->operator == OR)
			ft_current_operator_or(&current, status);
		else
		{
			write(2, "Unknown operator: '", 19);
			write(2, current->str, strlen(current->str));
			write(2, "'.\n", 3);
			return EXIT_FAILURE;
		}
	}
	return status;
}

void assign_operator(t_params *node)
{
	if (strcmp(node->str, "&&") == 0)
		node->operator = AND;
	else if (strcmp(node->str, "||") == 0)
		node->operator = OR;
	else if (strcmp(node->str, "&") == 0)
	{
		write(STDERR_FILENO, "error, incorrect operator '&'\n", 30);
		node->operator = ERROR;
	}
	else
		node->operator = NONE;
}

void free_subcommand_args(char **args)
{
	if (args != NULL)
	{
		int i = 0;
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void free_subcommands(t_params *sub_cmds)
{
	t_params *tmp;
	
	while (sub_cmds != NULL)
	{
		tmp = sub_cmds;
		sub_cmds = sub_cmds->next;
		if (tmp->str != NULL)
			free(tmp->str);
		if (tmp->cmd != NULL)
			free(tmp->cmd);
		free_subcommand_args(tmp->args);
		free(tmp);
	}
}
