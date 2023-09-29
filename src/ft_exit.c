/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:14:04 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/28 16:17:57 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

// int exit_code; add to structure !!!!!!!!!!!!!

int ft_count_arguments(char **arguments)
{
    int count = 0;
    while (arguments[count] != NULL)
    {
        count++;
    }
    return count;
}

// Function to handle the 'exit' command
void ft_exit(t_data *data)
{
    if (ft_count_arguments(data->arguments) > 2)
    {
        // Handle too many arguments
        ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
        // Set the exit code to indicate a failure
        exit(EXIT_FAILURE);
    }

    if (data->arguments[1] != NULL)
    {
        int exit_code = ft_atoi(data->arguments[1]);

        if (exit_code == 0 && ft_strcmp(data->arguments[1], "0") != 0)
        {
            // Handle invalid argument
            ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
            // Set the exit code to indicate a failure
            exit(EXIT_FAILURE);
        }

        // Set the exit code
        data->exit_code = exit_code;
    }
    else
    {
        // No argument provided, exit with a status of 0
        data->exit_code = 0;
    }

    // Set the stop flag to terminate the main shell loop
    data->stop_main = 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    t_data data;
    data.arguments = (char *[]){"exit", "42", NULL}; // Sample arguments

    printf("Before calling ft_exit:\n");
    printf("data->stop_main: %d\n", data.stop_main);

    ft_exit(&data);

    printf("After calling ft_exit:\n");
    printf("data->stop_main: %d\n", data.stop_main);

    return 0;
}
