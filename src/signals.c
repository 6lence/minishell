/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:16:37 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/08 15:18:14 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *get_global_data(void)
{
    static t_data *data;

    data = NULL;
    if (data == NULL)
	{
        data = (t_data *)malloc(sizeof(t_data));
        if (!data)
		{
            perror("Failed to allocate memory for global data");
            exit(EXIT_FAILURE);
        }
        // Initialize data id needed
        // ft_memset(data, 0, sizeof(t_data));
        // Initialize other fields as necessary
    }
    return data;
}

void ft_cleanup(void)
{
    t_data *data;

    data = get_global_data();
    // Clean up any allocated resources within data here
    free(data);
    // Optionally, reset the global data to NULL, so that subsequent calls to get_global_data will initialize a new object
    data = NULL;
}

void handle_sigint(int sig_num)
{
    t_data *data;

    data = get_global_data();
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
    sigaction(SIGQUIT, &ctrl_c, NULL);
}

void handle_sigquit(int sig_num)
{
    (void)sig_num; // Suppress unused parameter warning
    printf("do nothing, Ctrl+backslash is pressed\n"); // Print message indicating that Ctrl+\ was pressed
}

void signal_ctrl_back_slash(void)
{
    struct sigaction ctrl_back_slash;
    ctrl_back_slash.sa_handler = handle_sigquit;
    ctrl_back_slash.sa_flags = SA_RESTART;
    sigemptyset(&ctrl_back_slash.sa_mask);
    sigaction(SIGQUIT, &ctrl_back_slash, NULL);
}

void handle_eof(void) // Ctrl+D
{
    printf("Exiting...\n");
    ft_cleanup();
    exit(0);
}

void signal_ctrl_d(void)
{
    // The ctrl+D (EOF) handling would usually be in main loop where read input
    // This function isn't necessarily a signal handler, but a routine called when EOF is detected
}

/*
int main(void)
{
    t_data *data;

    data = get_global_data();
    signal_ctrl_c(); // Set up signal handler for ctrl+C
    signal_ctrl_back_slash(); // Set up signal handler for ctrl+\ .
    // Main loop for shell
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
            ft_cleanup();
            exit(0);
        }
        // Act on the entered line (execute command, etc.)
        printf("You entered: %s\n", line);
        free(line);
    }
    ft_cleanup(); // Cleanup resources on exit
    return (0);
}
*/
/*
gcc -Wall -Wextra -Werror src/signal_handling.c -lreadline
*/