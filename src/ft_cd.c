/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:11:37 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/25 14:29:20 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

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
