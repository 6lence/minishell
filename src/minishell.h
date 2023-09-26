/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:14:23 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/26 11:37:43 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>

# include "../libft/libft.h"

typedef struct s_data
{
	int		envp;
	int		stop_main;
	char	**params;
	char	*command;
	char	**arguments;
	int		in;
	int		out;
}		t_data;

/* minishell */
void	show_parameters(const char *parameters);

/* parsing */
void	get_command_arguments(const char *input,
			char *command, char ***arguments);
void	execute_command(t_data *l);

/* echo */
void	ft_echo(t_data *data);

/* pwd */
char	*ft_pwd();

#endif