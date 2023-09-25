/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:14:23 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/25 14:49:05 by miguel           ###   ########.fr       */
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

typedef struct s_data
{
	int		envp;
	int		stop_main;
	char	**params;
	char	*command;
	char	**arguments;
}		t_data;

/* minishell */
char	*readline(void);
void	show_parameters(const char *parameters);

/* parsing */
void	get_command_arguments(const char *input,
			char *command, char ***arguments);
void	execute_command(t_data *l);

#endif