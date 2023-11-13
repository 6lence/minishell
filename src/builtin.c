/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:21:48 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/13 14:19:50 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin_2(t_data *l, t_params *tmp)
{
	char	*command;
	int		result;

	result = 0;
	command = tmp->str;
	if (ft_strcmp(command, "env") == 0)
		result = ft_env(l);
	else if (ft_strcmp(command, "export") == 0)
		result = ft_export(l);
	else if (ft_strcmp(command, "unset") == 0)
		result = ft_unset(l);
	else if (ft_strcmp(command, "exit") == 0)
		result = ft_exit(l);
	return (result);
}

int	execute_builtin(t_data *l, t_params *tmp)
{
	int		result;
	char	*command;
	char	**arguments;
	char	*pwd;

	result = 0;
	command = tmp->str;
	arguments = linked_list_to_array(tmp->next);
	l->arguments = arguments;
	if (ft_strcmp(command, "echo") == 0)
		result = ft_echo(l);
	else if (ft_strcmp(command, "cd") == 0)
		result = ft_cd(l);
	else if (ft_strcmp(command, "pwd") == 0)
	{
		pwd = ft_pwd();
		printf("%s\n", pwd);
		free(pwd);
		result = 0;
	}
	else
		result = execute_builtin_2 (l, tmp);
	free(arguments);
	return (result);
}

void	linked_list_to_array_2(t_params *current, char **args)
{
	int		i;

	i = 0;
	while (current != NULL)
	{
		args[i] = current->str;
		current = current->next;
		i++;
	}
	args[i] = NULL;
}

char	**linked_list_to_array(t_params *tmp)
{
	int			count;
	t_params	*current;
	char		**args;

	count = 0;
	current = tmp;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	linked_list_to_array_2(tmp, args);
	return (args);
}
