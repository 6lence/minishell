/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:14:23 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/24 14:46:10 by mescobar         ###   ########.fr       */
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
# include <fcntl.h>
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
	int			envp_allocated;
	int			stop_main;
	char		**env_vars;
	char		*params;
	char		**params_split;
	char		*path;
	char		**arguments;
	int			tmp_file;
	int			pos;
	int			pipe;
	int			pipe_nb;
	DIR			*dir;
	int			in;
	int			out;
	int			exit_code;
	int			input;
	int			output;
	int			new_fd[2];
	int			old_fd[2];
	t_params	*list;
	t_signal	sig;
}		t_data;

/* minishell */
void	show_parameters(const char *parameters);
void	ft_pipe(t_data *l);
int		ft_access_verif(t_data *l, t_params *tmp);

/* parsing_1 */
void	get_command_arguments(const char *input,
			char *command, char **arguments);
void	execute_command(t_data *l, t_params *tmp);
int		ft_chained_args(t_data *l);
void	ft_pipe_presence(t_data *l);
void	ft_parsing(t_data *l);

/* parsing_2 */
char	**ft_search_path(char *str, t_data *l);
char	*ft_pathcmp(char *str, char *path);
int		ft_args(t_params *l);

/* parsing_3 */
int	ft_words(t_data *l);

/* parsing_4 */
void	ft_fill_split(t_data *l);

/* parsing_5 */
void	ft_look_dollar(t_data *l);

/* parsing_6 */
void	ft_look_in_out_put(t_data *l);
char	*ft_find_var(t_params *list, t_data *l);

/* builtin */
int		is_builtin(char *command);
int		execute_builtin(t_data *l, t_params *tmp);
char	**linked_list_to_array(t_params *tmp);

/* ft_cd */
void	print_env_variables(char **envp);
int		find_env_variable(char **envp, const char *var_name);
void	add_env_variable(char ***envp, char *argument);
void	handle_env_variable(char ***envp, const char *var_name, char *argument);
int		ft_cd(t_data *l);

/* ft_echo */
int		ft_echo(t_data *l);

/* ft_env */
int	ft_env(t_data *l);

/* ft_exit */
int		ft_count_arguments(char **arguments);
void	ft_exit(t_data *data);

/* ft_export */
int		ft_export(t_data *data);
int		array_length(char **array);

/* pwd */
char	*ft_pwd(void);

/* ft_unset */
int		is_proper_env(const char *env_name);
char	**ft_getenvvar(t_data *data, const char *name);
int		ft_unsetenv(t_data *data, const char *name);
int		ft_unset(t_data *data, char *arguments[]);

/* lstutils */
t_params	*ft_lstlast(t_params *l);
t_params	*ft_lstfirst(t_params *l);
int			ft_lstlen(t_params *l);
void		ft_lstprint(t_params *l);
t_params	*ft_lst_elem(t_params *l, int pos);

/* errors */
int		ft_direrror(t_data *l);
void	ft_free_all(t_data *l);

#endif