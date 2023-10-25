/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:10:15 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/25 12:44:31 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function to handle the -n option
static size_t	check_n(char **args)
{
	size_t	i;
	size_t	j;

	if (!args)
        return (0);
	i = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j++] == '-' && args[i][j] && args[i][j] == 'n')
		{
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] && args[i][j] != 'n')
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int ft_echo(t_data *l)
{
    int newline;
    int i;
    /*
    i = 0;
    while (l->arguments && l->arguments[i])
    {
        ft_putstr_fd("data->arguments[", 1);
        ft_putnbr_fd(i, 1);
        ft_putstr_fd("]: ", 1);
        ft_putstr_fd(l->arguments[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
	*/
    // Check if data or data->arguments is NULL
    if (!l || !l->arguments)
    {
        ft_putstr_fd("Error: missing data or arguments\n", 2);
        return (-1);
    }
    i = check_n(l->arguments); // Check for the -n option

    newline = (i == 0 || ft_strcmp(l->arguments[0], "-n") != 0); // Update newline based on -n option

    while (l->arguments[i])
    {
        write(STDOUT_FILENO, l->arguments[i], ft_strlen(l->arguments[i])); // Print each argument
        if (l->arguments[i + 1] != NULL) // If it's not the last argument, print a space
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline) // If the -n option was not used, print a newline
        write(STDOUT_FILENO, "\n", 1);

    return (0);
}


/*
int main()
{
    // Create a sample data structure
    t_data data;
    char *arguments[] = {"echo", "-n", "Hello,", "world!", NULL};
    data.arguments = arguments;

    // Call the ft_echo function
    ft_echo(&data);

    return 0;
}
*/

/*

STDIN_FILENO (0): Standard input, typically the keyboard.
STDOUT_FILENO (1): Standard output, typically the terminal where output is displayed.
STDERR_FILENO (2): Standard error, also typically the terminal for error messages.
*/
