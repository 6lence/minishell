/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:27:29 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/17 14:22:12 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_wildcard(t_params *params, char **env)
{
	t_params	*tmp;
	int			i;

	(void)env;
	tmp = params;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == '*')
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

t_params	*new_node(const char *cmd, char **args)
{
	t_params	*new_node;

	new_node = malloc(sizeof(t_params));
	new_node->cmd = ft_strdup(cmd);
	new_node->args = args;
	new_node->next = NULL;
	printf("Debug: Created new node - cmd: '%s'\n", new_node->cmd);
	return (new_node);
}

int	ft_wild_in(char *str1, char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str2[i])
	{
		if (str1[j] == '*')
			j++;
		if (str2[i + j] == str1[j])
		{
			j++;
			if (j == n)
				return (1);
		}
		else
		{
			i++;
			j = 0;
		}
	}
	return (0);
}

int	ft_in_wild(char *str, char s)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	**ft_verify(t_params *l, char **file_list)
{
	int		i;
	int		len;
	char	**res;
	t_params	*tmp;

	i = 0;
	len = 0;
	tmp = l;
	while (tmp && !ft_in_wild(tmp->str, '*'))
		tmp = tmp->next;
	while (file_list[i])
	{
		if (ft_wild_in(tmp->str, file_list[i], ft_strlen(tmp->str)))
			len++;
		i++;
	}
	res = ft_calloc(sizeof(char *), len + ft_res_len(l));
	i = 0;
	len = 0;
	while (l && !ft_in_wild(l->str, '*') && !ft_operator_cmp(l))
	{
		if (access(l->str, 0) == 0 && len == 0)
			res[len++] = ft_divide_path(l->str);
		else
			res[len++] = ft_strdup(l->str);
		l = l->next;
	}
	i = 0;
	while (file_list[i])
	{
		if (ft_wild_in(tmp->str, file_list[i], ft_strlen(tmp->str)))
			res[len++] = ft_strdup(file_list[i]);
		free(file_list[i]);
		i++;
	}
	free(file_list);
	return (res);
}

char	**execute_command_with_wildcards_loop(t_params *commands)
{
	DIR *d = opendir(".");
	if (d == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}

	char **file_list = NULL;
	int file_count = 0;
	struct dirent *dir;

	// Read directory entries once and store in file_list
	dir = readdir(d);
	while (dir != NULL)
	{
		file_list = ft_realloc(file_list, sizeof(char *) * (file_count + 1));
		file_list[file_count++] = ft_strdup(dir->d_name);
		dir = readdir(d);
	}
	closedir(d);
	file_list = ft_verify(commands, file_list);
	return (file_list);
}


/*
void	execute_command_with_wildcards(t_params *commands, char **envp)
{
	DIR	*d;

	d = opendir(".");
	if (d == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	if (commands != NULL)
		execute_command_with_wildcards_recursive(commands, envp, d);
	closedir(d);
}

void	execute_command_with_wildcards_recursive(t_params *current, \
				char **envp, DIR *d)
{
	char	**new_args;
	char	**file_list;
	int		arg_count;
	int		file_count;
	int		i;
	struct	dirent *dir;

	file_count = 0;
	file_list = NULL;
	i = 0;

	if (!current)
		return ;
	printf("Debug: Entering execute_command_with_wildcards_recursive\n");
	while ((dir = readdir(d)) != NULL)
	{
		file_list = ft_realloc(file_list, sizeof(char *) * (file_count + 1));
		file_list[file_count++] = ft_strdup(dir->d_name);
	}
	printf("Debug: file_list populated with %d files\n", file_count);
	//call count_arguments
	arg_count = 0;
	if (current->str)
		printf("Debug: Processing command '%s'\n", current->str);
	else
		printf("Debug: Current command is NULL\n");
	printf("Debug: Calling count_arguments\n");
	count_arguments(current, &arg_count, file_list);
	printf("Debug: count_arguments returned with count: %d\n", arg_count);
	printf("Debug: Found %d arguments for command '%s'\n", arg_count, current->str);

	new_args = malloc((arg_count + 1) * sizeof(char *));
	if (new_args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	assign_arguments(current, new_args, d, 0, arg_count);
	printf("Debug: Executing command '%s' with arguments:\n", current->str);
	while (i < file_count)
	{
        free(file_list[i]);
		i++;
    }
    free(file_list);
	free(new_args);
	if (current->next != NULL)
	{
		printf("Debug: Recursively calling execute_command_with_wildcards_recursive for next command\n");
		execute_command_with_wildcards_recursive(current->next, envp, d);
	}
	printf("Debug: Exiting execute_command_with_wildcards_recursive\n");
}
*/

int	ft_in_2(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void count_arguments(t_params *current, int *count, char **file_list)
{
	t_params	*tmp;
	int			i;

	tmp = current;
	i = 0;

	printf("Debug: Entering count_arguments\n");  // Debug

	if (file_list == NULL)
	{
		printf("Debug: file_list is NULL\n");  // check for NULL file_list
    	return;
	} //end debug

	while (tmp)
	{
		printf("Debug: Processing tmp->str: %s\n", tmp->str ? tmp->str : "NULL");
		if (tmp->str && ft_in_2(tmp->str, '*'))
		{
			while (file_list[i] != NULL)
			{
				printf("Debug: Checking file_list[%d]: %s against %s\n", i, file_list[i], tmp->str);
				if (matches_wildcard(tmp->str, file_list[i]))
				{
					(*count)++;
					printf("Debug: Matched. Incrementing count to %d\n", *count);
				}
				i++;
			}
		}
		else if (tmp->str)
		{
			(*count)++;
			printf("Debug: No wildcard. Incrementing count to %d\n", *count);
		}
		tmp = tmp->next;
	}
	printf("Debug: Exiting count_arguments. Total count: %d\n", *count);
}

void assign_arguments(t_params *l, char **new_args, DIR *d, int index, int arg_count)
{
	struct dirent	*dir;

	printf("Debug: Starting to assign arguments\n");
	while (l)
	{
		if (l && index < arg_count)
		{
			printf("Debug: Assigning argument '%s'\n", l->str); // Debug
			if (index == 1 && ft_strchr(l->str, '*'))
			{
				// Handle wildcard
				printf("Debug: Argument '%s' contains a wildcard\n", l->str); // Debug
				while ((dir = readdir(d)) != NULL)
				{
					printf("Debug: Checking if '%s' matches '%s'\n", dir->d_name, l->str); // Debug print
					if (matches_wildcard(l->str, dir->d_name))
					{
						printf("Debug: Match found: %s\n", dir->d_name); // Debug print
						new_args[index] = dir->d_name;
						break;
					}
				}
				if (dir == NULL) // No match found
				{
					printf("Debug: No match found for wildcard '%s'\n", l->str); // Debug print
					new_args[index] = l->str; // Keep original arg if no match
				}
			}
			else
				new_args[index] = l->str;
		}
		else
			new_args[arg_count] = NULL;
		l = l->next;
	}
}

void	execute_child_process(const char *cmd, char **args, char **envp, DIR *d)
{
	int	status;

	pid_t pid = fork();
	if (pid == 0)
	{ // Child process
		execve(cmd, args, envp);
		perror("execve");
		closedir(d);
		free(args);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{ // Fork failed
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0); // Parent process
}

int	matches_wildcard(const char *str, const char *pattern)
{
	const char	*str_backup;
	const char	*pattern_backup;

	str_backup = NULL;
	pattern_backup = NULL;
	while (*str)
	{
		if (*pattern == '*')
		{
			// If a star, then compare the rest of pattern with the next character
			pattern++;
			if (!*pattern)
			{
				return (1); // If at the end of the pattern, it's a match regardless of the string
			}
			pattern_backup = pattern;
			str_backup = str + 1;
		}
		else if (*pattern == '?' || *pattern == *str) // ? used to represent any single character
		{
			// Advance both pointers if they are equal or it's a single character wildcard
			pattern++;
			str++;
		}
		else if (str_backup)
		{
			// If there was a star, and the current characters don't match
			// reset the current pattern to the character next to the last star
			// and set the current string to the next character of the last remembered string
			pattern = pattern_backup;
			str = str_backup++;
		}
		else
		{
			// If they don't match and there are no stars to fall back to, it's not a match
			return (0);
		}
	}
	while (*pattern == '*')
	{
		pattern++;
	}
	// If we're at the end of the pattern, it's a match
	return (*pattern == '\0');
}

/*
void	execute_command_with_wildcards_recursive(t_params *current, \
				char **envp, DIR *d)
{
	char	**new_args;
	char	**file_list;
	int		arg_count;
	int		file_count;
	int		i;
	struct	dirent *dir;

	file_count = 0;
	file_list = NULL;
	i = 0;

	printf("Debug: Entering execute_command_with_wildcards_recursive\n");
	while ((dir = readdir(d)) != NULL)
	{
		file_list = ft_realloc(file_list, sizeof(char *) * (file_count + 1));
		file_list[file_count++] = ft_strdup(dir->d_name);
	}
	printf("Debug: file_list populated with %d files\n", file_count);
	//call count_arguments
	arg_count = 0;
	if (current->str)
		printf("Debug: Processing command '%s'\n", current->str);
	else
		printf("Debug: Current command is NULL\n");
	printf("Debug: Calling count_arguments\n");
	count_arguments(current, &arg_count, file_list);
	printf("Debug: count_arguments returned with count: %d\n", arg_count);
	printf("Debug: Found %d arguments for command '%s'\n", arg_count, current->str);

	new_args = malloc((arg_count + 1) * sizeof(char *));
	if (new_args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	assign_arguments(current, new_args, d, 0, arg_count);
	printf("Debug: Executing command '%s' with arguments:\n", current->str);
	while (i < file_count)
	{
        free(file_list[i]);
		i++;
    }
    free(file_list);
	free(new_args);
	if (current->next != NULL)
	{
		printf("Debug: Recursively calling execute_command_with_wildcards_recursive for next command\n");
		execute_command_with_wildcards_recursive(current->next, envp, d);
	}
	printf("Debug: Exiting execute_command_with_wildcards_recursive\n");
}

*/

// char	**get_directory_files(int *file_count)
// {
// 	DIR				*d;
// 	struct dirent	*dir;
// 	char			**filenames;
// 	int				count;

// 	filenames = NULL;
// 	count = 0;

//     d = opendir(".");
//     if (!d)
// 	{
//         perror("opendir");
//         return NULL;
//     }

//     while ((dir = readdir(d)) != NULL)
// 	{
//         filenames = realloc(filenames, sizeof(char *) * (count + 1));
//         filenames[count++] = strdup(dir->d_name);
//     }

//     closedir(d);
//     *file_count = count;
//     return filenames;
// }

/*
void	execute_command_with_wildcards(t_params *commands, char **envp)
{
	DIR				*d;
	struct dirent	*dir;
	const char		**new_args;
	t_params		*current;

	d = opendir(".");
	if (d == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	new_args = malloc(3 * sizeof(char *));
	if (new_args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	current = commands;
	while (current != NULL)
	{
		pid_t	pid = fork();
		if (pid == 0)
		{
			while ((dir = readdir(d)) != NULL)
			{
				if (ft_strstr(dir->d_name, current->args[1] + 1))
				{
					new_args[0] = current->cmd;
					new_args[1] = dir->d_name;
					new_args[2] = NULL;
					execve(current->cmd, (char *const *)new_args, envp);
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			closedir(d);
			free(new_args);
			exit(EXIT_SUCCESS);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else
		{
			int	status;
			waitpid(pid, &status, 0);
		}
		current = current->next;
	}
	free(new_args);
}

void	delete_list(t_params *head)
{
	t_params	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
		free(tmp);
	}
}
*/
/*
- DIR is a datatype representing a directory stream in C. It is used to manage and
handle directories as streams, allowing you to operate on the directory's content.
- d is a pointer to a DIR type, and it holds the reference to the directory stream
opened by the opendir() function.
- When you call opendir(), it returns a pointer of type DIR that you can use to
read the directory’s contents or close the directory later.

- struct dirent is a structure type used to represent directory entries. It is used
when reading from a directory stream, providing information about the files and
subdirectories within.
- dir is a pointer to a struct dirent, and it holds the reference to directory
entries when you read them using readdir().
- The readdir() function returns a pointer to a struct dirent representing the
next directory entry in the directory stream. It returns NULL after the last
directory entry.
*/
