/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:00:56 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/26 17:01:11 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **arguments)
{
    if (arguments[1] == NULL)
    {
        ft_putstr_fd("cd: missing arguments\n", 2); // print message error 
        return 1;
    }
    else if (chdir(arguments[1]) == -1)
    {
        // If chdir returns -1, an error occurred
        perror("cd"); // Print the error message
        return 1;      // Return a non-zero value to indicate failure
    }

    return 0;
}