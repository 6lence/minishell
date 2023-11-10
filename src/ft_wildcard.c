/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:27:29 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/10 15:55:29 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_wildcard(t_params *params, char **env)
{
	t_params    *tmp;
	int         i;
	int         res;

	(void)env;
	res = 0;
	tmp = params;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == '*')
				res = 1;
			i++;
		}
		tmp = tmp->next;
	}
	return (res);
}

t_params	*new_node(const char *cmd, char **args)
{
	t_params	*new_node;

	new_node = malloc(sizeof(t_params));
	new_node->cmd = ft_strdup(cmd);
	new_node->args = args;
	new_node->next = NULL;
	return (new_node);
}

void execute_command_with_wildcards(t_params *commands, char **envp)
{
    DIR *d;
    t_params *current = commands;

    d = opendir(".");
    if (d == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    if (current != NULL)
    {
        execute_command_with_wildcards_recursive(current, envp, d);
    }

    closedir(d);
}

void execute_command_with_wildcards_recursive(t_params *current, char **envp, DIR *d) 
{
    char **new_args;
    int arg_count;

	arg_count = 0;

    printf("Debug: Processing command '%s'\n", current->cmd); // Debug print
    
	count_arguments(current->args, &arg_count);
    printf("Debug: Found %d arguments for command '%s'\n", arg_count, current->cmd); // Debug print
    new_args = malloc((arg_count + 1) * sizeof(char *));
    if (new_args == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Assign arguments
    assign_arguments(current->args, new_args, d, 0, arg_count);
    
    // Execute the command
    execute_child_process(current->cmd, (char**)new_args, envp, d);
    
    free(new_args);

    if (current->next != NULL)
    {
        execute_command_with_wildcards_recursive(current->next, envp, d);
    }
}

void count_arguments(char **args, int *count) 
{
    if (args[*count] != NULL)
    {
        (*count)++;
        count_arguments(args, count);
    }
}

void assign_arguments(char **args, char **new_args, DIR *d, int index, int arg_count) 
{
    struct dirent *dir;
	
	if (index < arg_count)
    {
        if (index == 1 && ft_strchr(args[index], '*'))
        {
            // Handle wildcard
			printf("Debug: Argument '%s' contains a wildcard\n", args[index]); // Debug
            rewinddir(d); // Reset the directory stream
            while ((dir = readdir(d)) != NULL)
            {
                printf("Debug: Checking if '%s' matches '%s'\n", dir->d_name, args[index]); // Debug print
				if (matches_wildcard(args[index], dir->d_name))
                {
                    printf("Debug: Match found: %s\n", dir->d_name); // Debug print
					new_args[index] = dir->d_name;
                    break;
                }
            }
            if (dir == NULL) // No match found
            {
                printf("Debug: No match found for wildcard '%s'\n", args[index]); // Debug print
				new_args[index] = args[index]; // Keep original arg if no match
            }
        }
        else
        {
            new_args[index] = args[index];
        }
        assign_arguments(args, new_args, d, index + 1, arg_count); // Recursively call for next index
    }
    else
    {
        new_args[arg_count] = NULL;
    }
}

void	execute_child_process(const char *cmd, char **args, char **envp, DIR *d)
{
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
	{ // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
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
                return 1; // If at the end of the pattern, it's a match regardless of the string
            }
            pattern_backup = pattern;
            str_backup = str + 1;
        }
		else if (*pattern == '?' || *pattern == *str)
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
            return 0;
        }
    }
    while (*pattern == '*')
	{
        pattern++;
    }

    // If we're at the end of the pattern, it's a match
    return *pattern == '\0';
}

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
