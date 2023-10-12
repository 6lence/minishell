/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:14:04 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/12 09:33:01 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_arguments(char **arguments)
{
	int	count;

	count = 0;
	while (arguments[count] != NULL)
	{
		count++;
	}
	return (count);
}

// Function to handle the 'exit' command
void	ft_exit(t_data *data)
{
	int	exit_code;

	if (ft_count_arguments(data->arguments) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (data->arguments[1] != NULL)
	{
		exit_code = ft_atoi(data->arguments[1]);
		if (exit_code == 0 && ft_strcmp(data->arguments[1], "0") != 0)
		{
            // Handle invalid argument
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		data->exit_code = exit_code; // Set the exit code
	}
	else
	{
		data->exit_code = 0; // No argument provided, exit with a status of 0
	}
	data->stop_main = 0; // Set the stop flag to terminate the main shell loop
}
/*
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
*/
