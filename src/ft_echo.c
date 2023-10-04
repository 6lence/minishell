/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:10:15 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/04 10:38:56 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function to handle the -n option
static size_t check_n(char **args)
{
    size_t i;
    size_t j;

    i = 0;
    while (args[++i])
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
    }
    return (i);
}

int ft_echo(t_data *data)
{
    int newline;
    int i;

    newline = 1; // Flag to print a newline at the end
    i = check_n(data->arguments);
    
    if (i > 1) // if i is greater than 1, it means -n option is present
        newline = 0;

    if (data->arguments[1] == NULL)
    {
        ft_putstr_fd("echo: missing arguments\n", 2);
        return; // Return without an argument because the return type is void
    }
    while (data->arguments[i] != NULL)
    {
        // Print each argument
        write(STDOUT_FILENO, data->arguments[i], ft_strlen(data->arguments[i]));

        // Print a space between arguments
        if (data->arguments[i + 1] != NULL)
        {
            // File descriptor for the standard output (stdout)
            write(STDOUT_FILENO, " ", 1);
        }
        i++;
    }
    // Print a newline if the -n option was not used
    if (newline)
    {
        write(STDOUT_FILENO, "\n", 1);
    }
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