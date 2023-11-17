/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_priorities_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:46:05 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/17 10:55:40 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NONE 0
#define AND 1

void	ft_no_curr_no_next(char *cmd_str, t_params **current,
			t_params **temp_cmd_node)
{
	size_t	total_length;

	total_length = ft_strlen((*current)->str) + \
			ft_strlen((*current)->next->str) + 2;
	cmd_str = malloc(total_length);
	if (cmd_str == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(cmd_str, (*current)->str);
	ft_strcat(cmd_str, " ");
	ft_strcat(cmd_str, (*current)->next->str);
	(*temp_cmd_node) = create_temp_command_node(cmd_str);
	free(cmd_str);
}

void	ft_current_operator_none(t_params **current, int *status, char *cmd_str)
{
	t_params	*temp_cmd_node;

	temp_cmd_node = (*current);
	if ((*current)->next != NULL && (*current)->next->operator == NONE)
		ft_no_curr_no_next(cmd_str, current, &temp_cmd_node);
	else
		temp_cmd_node = create_temp_command_node((*current)->str);
	*status = execute_operator(temp_cmd_node);
	free_t_params(temp_cmd_node);
	if ((*current)->next != NULL && (*current)->next->operator == NONE)
		*current = (*current)->next->next;
	else
		*current = (*current)->next;
}

void	ft_current_operator_and(t_params **current, int status)
{
	if (status != 0)
	{
		while ((*current) != NULL && (*current)->operator == AND)
			(*current) = (*current)->next;
	}
	else
		(*current) = (*current)->next;
}

void	ft_current_operator_or(t_params **current, int status)
{
	if (status == 0)
	{
		while ((*current) && (*current)->operator != AND)
			(*current) = (*current)->next;
	}
	else
		(*current) = (*current)->next;
}

void	ft_non_operator(char *cmd_str, t_params *temp, int a)
{
	char	**args;
	int		i;
	int		j;

	args = ft_split(cmd_str, ' ');
	i = 0;
	if (args[i] != NULL)
	{
		temp->cmd = ft_strdup(args[i++]);
		temp->args = (char **)malloc(sizeof(char *) * a);
		temp->args[0] = ft_strdup(temp->cmd);
		j = 1;
		while (args[i] != NULL && j < a - 1)
			temp->args[j++] = ft_strdup(args[i++]);
		temp->args[j] = NULL;
	}
	i = 0;
	while (args[i] != NULL)
		free(args[i++]);
	free(args);
}
