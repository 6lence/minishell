/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:14:23 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/28 14:43:41 by mescobar         ###   ########.fr       */
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

typedef struct s_params
{
	struct s_params	*prev;
	char			*str;
	int				pos;
	struct s_params	*next;
}					t_params;

typedef struct s_signal
{
	int	stop;
}		t_signal;

typedef struct s_data
{
	char		**envp;
	int			stop_main;
	char		**params;
	char		*command;
	char		**arguments;
	char		*path;
	DIR			*dir;
	int			in;
	int			out;
	t_params	*list;
	t_signal	*sig;
}		t_data;

/* minishell */
void	show_parameters(const char *parameters);

/* parsing */
void	get_command_arguments(const char *input,
			char *command, char **arguments);
void	execute_command(t_data *l);
int		ft_direrror(t_data *l);
int		ft_chained_args(t_data *l);

/* echo */
void	ft_echo(t_data *data);

/* pwd */
char	*ft_pwd();

#endif