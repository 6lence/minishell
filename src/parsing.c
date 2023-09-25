/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:10:34 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/20 09:16:52 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to parse user input and return command and arguments
void parse_input(const char *input, char **command, char ***arguments)
{
    char **tokens = ft_split(input, ' ');
    if (!tokens || !tokens[0])
    {
        // If no tokens found or the first token is empty, return NULL values
        *command = NULL;
        *arguments = NULL;
        return;
    }

    // The first token is the command
    *command = tokens[0];

    // The rest of the tokens are arguments
    *arguments = &tokens[1];
}

// Function to execute a command with its arguments
void execute_command(const char *command, char *const arguments[])
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0)
    {
        // This code runs in the child process
        if (execve(command, arguments, NULL) == -1)
        {
            // If execve returns, an error occurred
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // This code runs in the parent process
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    }
}
