/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:21:48 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/02 11:11:31 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to check  commands
// Function to check and execute commands
int ft_check_commands(const char *command, char **arguments, t_data *data)
{
    if (ft_strcmp(command, "echo") == 0)
    {
        ft_echo(arguments);
        return 0; // success
    }
    if (ft_strcmp(command, "cd") == 0)
    {
        ft_cd(arguments);
        return 0; // success
    }
    if (ft_strcmp(command, "pwd") == 0)
    {
        ft_pwd();
        return 0;
    }
    if (ft_strcmp(command, "export") == 0)
    {
        ft_export(arguments);
        return 0;
    }
    if (ft_strcmp(command, "unset") == 0)
    {
        ft_unset(data, arguments);
        return 0;
    }
    if (ft_strcmp(command, "env") == 0)
    {
        ft_env(arguments);
        return 0;
    }
    if (ft_strcmp(command, "exit") == 0)
    {
        ft_exit(arguments);
        return 0;
    }
    return 1; // failure
}
