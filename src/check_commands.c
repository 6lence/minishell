/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:21:48 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/25 13:37:22 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to check  commands
// Function to check and execute commands
int ft_check_execute(const char *command, char **arguments)
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


    return 1; // failure
}
