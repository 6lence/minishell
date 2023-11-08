/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:16:57 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/08 11:36:12 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *get_global_data(void)
{
    static t_data *data = NULL;
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
void handle_sigint(int sig_num)
{
    t_data *data = get_global_data();
    if (sig_num == SIGINT && data != NULL)
    {
        data->sig.stop = 1;
        write(1, "\n", 1);
        write(1, "$ ", 2);
        // Handle other necessary actions upon SIGINT
        // exit(0);
    }
    else if (sig_num == SIGQUIT && data != NULL)
    {
        //
        write(1, "lala\n", 5);
    }
}
void signal_ctrl_c(void) //in main
{
    struct sigaction ctrl_c;
    ctrl_c.sa_handler = handle_sigint;
    ctrl_c.sa_flags = SA_RESTART;
    sigemptyset(&ctrl_c.sa_mask);
    sigaction(SIGINT, &ctrl_c, NULL);
    sigaction(SIGQUIT, &ctrl_c, NULL);
}
void cleanup(void)
{
    t_data *data = get_global_data();
    // Clean up any allocated resources within data here
    // Then free data itself
    free(data);
}
int main(void)
{
    t_data *data = get_global_data();
    signal_ctrl_c();

    while (1)
    {
        if (data->sig.stop == 1)
        {
            data->sig.stop = 0;
            write(1, "$ ", 2);
        }
        char *line = readline("$ ");
        if (!line)
        {
            // Handle end of file (Ctrl+D)
            printf("Exiting.\n");
            cleanup();
            exit(0);
        }
        // Example: act on the line
        // You'd parse and execute the entered command here
        printf("You entered: %s\n", line);
        free(line);
        // For testing, exit on a specific command (e.g., "exit")
        if (strcmp(line, "exit") == 0)
        {
            cleanup();
            exit(0);
        }
    }
    // If break out of the loop, ensure to clean up
    cleanup();
    return 0;
}
/*
gcc -Wall -Wextra -Werror src/signal.c -lreadline
*/