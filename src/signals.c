/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:16:37 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/07 16:19:39 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig_num)
{
    t_data *data = get_global_data();
    
    if (sig_num == SIGINT && data != NULL)
    {
        data->sig.stop = 1;
        write(1, "\n", 1);
        // Set flag to indicate SIGINT was received
    }
}

void signal_ctrl_c(void)
{
    struct sigaction ctrl_c;

    ctrl_c.sa_handler = handle_sigint;
    ctrl_c.sa_flags = SA_RESTART;
    sigemptyset(&ctrl_c.sa_mask);
    sigaction(SIGINT, &ctrl_c, NULL);
}

void handle_sigquit(int sig_num)
{
    (void)sig_num; // Suppress unused parameter warning
	// Do nothing special for ctrl+\ 
}

void signal_ctrl_back_slash(void)
{
    struct sigaction ctrl_back_slash;

    ctrl_back_slash.sa_handler = handle_sigquit;
    ctrl_back_slash.sa_flags = SA_RESTART;
    sigemptyset(&ctrl_back_slash.sa_mask);
    sigaction(SIGQUIT, &ctrl_back_slash, NULL);
}

void handle_eof(void)
{
    printf("Exiting.\n");
    cleanup();
    exit(0);
}

void signal_ctrl_d(void)
{
    // The ctrl+D (EOF) handling would usually be in your main loop where you read input
    // This function isn't necessarily a signal handler, but a routine called when EOF is detected
}

int main(void)
{
    t_data *data = get_global_data();

    signal_ctrl_c(); // Set up signal handler for ctrl+C
    signal_ctrl_back_slash(); // Set up signal handler for ctrl+\

    // Main loop for your shell
    while (1)
    {
        if (data->sig.stop == 1)
        {
            data->sig.stop = 0;
            // handle SIGINT here, like printing a new prompt
            write(1, "$ ", 2);
        }

        char *line = readline("$ ");
        if (!line)
        {
            // Detect EOF (ctrl+D) and call handler function
            handle_eof();
        }

        // For testing, exit on a specific command (e.g., "exit")
        if (strcmp(line, "exit") == 0)
        {
            cleanup();
            exit(0);
        }

        // Act on the entered line (execute command, etc.)
        printf("You entered: %s\n", line);
        free(line);
    }

    cleanup(); // Cleanup resources on exit
    return (0);
}
