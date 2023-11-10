/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:14:23 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/10 10:51:42 by ashalagi         ###   ########.fr       */
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
	struct s_params		*prev;
	char				*str;
	int					pos;
	struct s_params		*next;
	char				*cmd;
	int					operator;
	char				**args;
}						t_params;

typedef struct s_var
{
	char			*var;
	struct s_var	*next;
}					t_var;

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
	int			commands;
	int			pipe;
	int			pipe_nb;
	DIR			*dir;
	int			in;
	int			out;
	int			var_out;
	int			exit_code;
	int			tmp_in;
	int			tmp_out;
	int			*child_pid;
	int			child_pos;
	int			new_fd[2];
	int			old_fd[2];
	t_params	*list;
	t_var		*var;
	t_signal	sig;
}		t_data;

/* minishell */
void		show_parameters(const char *parameters);
void		ft_pipe(t_data *l);
char		*ft_access_verif(t_data *l, t_params *tmp);
int			ft_chevron_cmp(t_params *params);
void		ft_increment(t_params **t);

/* parsing_1 */
void		get_command_arguments(const char *input,
				char *command, char **arguments);
void		execute_command(t_data *l, t_params *tmp);
int			ft_chained_args(t_data *l);
void		ft_pipe_presence(t_data *l);
void		ft_parsing(t_data *l);

/* parsing_2 */
char		**ft_search_path(char *str, t_data *l);
char		*ft_pathcmp(char *str, char *path);
int			ft_look_pipe(t_params **tmp, t_data *l);
int			ft_args(t_params *l);

/* parsing_3 */
int			ft_words(t_data *l);
int			ft_operator_cmp(t_params *tmp);
int			ft_count_command(t_data *l);

/* parsing_4 */
void		ft_fill_split(t_data *l);

/* parsing_5 */
void		ft_look_dollar(t_data *l);

/* parsing_6 */
void		ft_look_out_put(t_params *tmp, t_data *l);
char		*ft_find_var(t_params *list, t_data *l);

/*  parsing_7 */
int			ft_add_var(t_data *l);
void		ft_free_paranthese(t_params *params);

/*  parsing_8 */
void		ft_verif_tmp_var(t_params *tmp, t_data *l, int i, int b);
int			ft_only_spaces(char *str);

/* parsing_9 */
void		ft_open_simple_out(t_params *tmp, char *ct, t_data *l);
void		ft_open_simple_in(t_params *tmp, char *ct, t_data *l);
void		ft_open_double_out(t_params *tmp, char *ct, t_data *l);

/* parsing_10 */
void		ft_look_in(t_params *tmp, t_data *l);

/* parsing_11 */
void		ft_words_2(t_data *l, int *i, int *words);
void		ft_words_1(t_data *l, int *i, int *words);

/* utils */
int			is_builtin(char *command);
int			execute_builtin(t_data *l, t_params *tmp);
char		**linked_list_to_array(t_params *tmp);
void		ft_parent(t_data *l, pid_t child_pid);
void		ft_execute_part_1(t_params *tmp);

/* utils_2 */
char		**ft_absolute_path(t_data *l);
char		**ft_arguments(t_params *params);

/* ft_cd */
void		print_env_variables(char **envp);
int			find_env_variable(char **envp, const char *var_name);
void		add_env_variable(char ***envp, char *argument);
void		handle_env_variable(char ***envp,
				const char *var_name, char *argument);
int			ft_cd(t_data *l);

/* ft_echo */
int			ft_echo(t_data *l);

/* ft_env */
int			ft_env(t_data *l);

/* ft_exit */
int			ft_count_arguments(char **arguments);
int			ft_exit(t_data *l);

/* ft_export */
int			ft_export(t_data *l);
int			array_length(char **array);
int			add_or_update_env(t_data *data, char *key, char *value);

/* pwd */
char		*ft_pwd(void);

/* ft_unset */
int			is_proper_env(const char *env_name);
char		**ft_getenvvar(t_data *data, const char *name);
int			ft_unsetenv(t_data *data, const char *name);
t_params	*ft_get_nth_param(t_params *list, int n);
int			ft_unset(t_data *l);

/* ft_unset_2 */
void		ft_exit_code(int *err_flag, t_data *l);
void		ft_is_not_proper_variable(char *key, int *error_flag);
void		ft_is_not_proper_env(t_params *element, int *error_flag);

/* execute_priorities */
t_params	*create_temp_command_node(char *cmd_str);
int			contains_logical_operators(t_params *tmp);
int			execute_operator(t_params *cmd);
int			ft_execute_priorities(t_params *commands);
void		assign_operator(t_params *node);
void		free_subcommand_args(char **args);
void		free_subcommands(t_params *sub_cmds);

/* lstutils */
t_params	*ft_lstlast(t_params *l);
t_params	*ft_lstfirst(t_params *l);
int			ft_lstlen(t_params *l);
void		ft_lstprint(t_params *l);
t_params	*ft_lst_elem(t_params *l, int pos);

/* lstutils_2 */
int			ft_lstsize(t_params *l);
t_params	*ft_list_elem(t_params *l, int pos);

/* ft_utils */
char		*ft_strcat(char *s1, const char *s2);

/*  childs  */
void		ft_childs(t_data *l);

/* errors */
int			ft_direrror(t_data *l);

/* ft_free */
void		ft_free_list(t_params *l);
void		ft_free_split(char **str, int len);
void		ft_free_split_2(char **split);
void		ft_free_all(t_data *l);
void		free_resources(char **args, char *cmd_no_paren, t_params *temp);
void		ft_clean_up(t_data *l);

/* ft_wildcard */
t_params	*new_node(const char *cmd, char **args);
void		delete_list(t_params *head);
void		execute_command_with_wildcards(t_params *commands, char **envp);

/* signals */
void		setup_signal_handlers(void);
void		handle_sigint(int signum);
void		handle_sigquit(int signum);

#endif
