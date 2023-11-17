/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:16:37 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/17 15:07:56 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pid_t global_child_pid = -1;

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

// The SIGINT signal handler
void	handle_sigint(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
void setup_signal_handlers(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;			// Set the handler for SIGINT
	sigemptyset(&sa.sa_mask);	// Clear all signals from the signal mask
	sa.sa_flags = SA_SIGINFO | SA_RESTART;	//  syscalls are restarted if interrupted
	sigaction(SIGINT, &sa, NULL);			// Assign the handler for SIGINT

	sa.sa_handler = SIG_IGN;		//handle_sigquit // Set the handler for SIGQUIT
	sigaction(SIGQUIT, &sa, NULL);			// Assign the handler for SIGQUIT
}

// The SIGINT signal handler
void handle_sigint(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);	// Write a newline character
	rl_on_new_line();				// Tell readline to move to a new line
	rl_replace_line("", 0);			// Clear the current input
	rl_redisplay();					// Redisplay the prompt
}
*/