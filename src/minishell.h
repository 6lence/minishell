/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:14:23 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/16 15:30:42 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>

# include "../libft/libft.h"

/* minishell */
char *readline();
void show_parameters(const char *parameters);

/* parsing */
void parse_input(const char *input, char **command, char ***arguments);
void execute_command(const char *command, char *const arguments[]);

#endif