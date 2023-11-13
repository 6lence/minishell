/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_priorities_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:33:07 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/13 14:33:46 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_subcommand_args(char **args)
{
	int	i;

	if (args != NULL)
	{
		i = 0;
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void	free_subcommands(t_params *sub_cmds)
{
	t_params	*tmp;

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
