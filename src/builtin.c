/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:21:48 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/04 13:37:00 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1); // command is a built-in command.
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
	return (0); //no match
}

int		execute_builtin(t_data *data)
{
	int		result;

	result = 0;
	if (ft_strcmp(data->command, "echo") == 0)
		result = ft_echo(data->arguments); // Adjusted based on assumed ft_echo signature
	if (ft_strcmp(data->command, "cd") == 0)
        result = ft_cd(data); // Adjusted based on assumed ft_cd signature
	if (ft_strcmp(data->command, "pwd") == 0)
		result = ft_pwd(); // No adjustment needed if ft_pwd doesn't require parameters
	if (ft_strcmp(data->command, "env") == 0)
		ft_env(data->envp); // Adjusted based on assumed ft_env signature
	if (ft_strcmp(data->command, "export") == 0)
		result = ft_export(data->arguments); // Adjusted based on assumed ft_export signature
	if (ft_strcmp(data->command, "unset") == 0)
		result = ft_unset(data->arguments, data->envp); // Adjusted based on assumed ft_unset signature
	return (result);
}


/*
if (is_builtin(data->command))
{
    result = execute_builtin(&data);
}
*/
