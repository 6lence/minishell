/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:16:57 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/05 21:12:22 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data g_data; // Reference the global variable

void handle_sigint(int sig_num, siginfo_t *info, void *ucontext)
{
    (void)info;
    (void)ucontext;
    if (sig_num == SIGINT)
    {
        // handle the SIGINT signal
        // Manipulate s_data structure as needed
        // set a flag in your structure indicating the signal was received
        // global_data is a pointer to s_data structure
        global_data->sig.stop = 1;

        // Add any other handling code as needed
        write(1, "\n", 1);
        // Possibly print a new prompt or take other appropriate action
    }
}

void signal_ctrl_c(t_data *data)
{
    struct sigaction ctrl_c;

    global_data = data; // assuming global_data is a global pointer to t_data

    ctrl_c.sa_sigaction = handle_sigint;
    ctrl_c.sa_flags = SA_SIGINFO; // Use SA_SIGINFO to use sa_sigaction instead of sa_handler
    sigemptyset(&ctrl_c.sa_mask);
    sigaction(SIGINT, &ctrl_c, NULL);
}
