/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:14:04 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/27 11:08:30 by mescobar         ###   ########.fr       */
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

int	ft_exit(t_data *l)
{
	int	exit_code;
	t_params *arguments = l->list;

	// Getting the number of arguments from the linked list
	int arg_count = ft_lstsize(arguments);

	if (arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (arg_count > 1)
	{
		arguments = arguments->next; // Skipping the command name ('exit')
		exit_code = ft_atoi(arguments->str);
		if (exit_code == 0 && ft_strcmp(arguments->str, "0") != 0)
		{
			// Handle invalid argument
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		l->exit_code = exit_code; // Set the exit code
	}
	else
	{
		l->exit_code = 0; // No argument provided, exit with a status of 0
	}
	l->stop_main = 0; // Set the stop flag to terminate the main shell loop
	return (0);
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
