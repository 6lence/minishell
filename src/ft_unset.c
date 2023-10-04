/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:15:03 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/04 10:54:27 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"
#include <stddef.h> // For NULL definition

// Function to check if the argument is a proper environment variable name
int is_proper_env(const char *env_name)
{
    int	i;

	i = 0;
    while (env_name[i])
    {
        if (!(ft_isalnum((unsigned char)env_name[i]) || env_name[i] == '_'))
        {
            return 0; // Not a proper environment variable name
        }
        i++;
    }
    return 1; // Proper environment variable name
}

static char	**getenvvar(const char *name)
{
	extern char **environ;
	int			i;
	int			j;

	if (name)
	{
		i = 0;
		while (environ[i])
		{
			j = 0;
			while (name[j] && environ[i][j] && name[j] == environ[i][j])
				++j;
			if (environ[i][j] != '=' || name[j])
				++i;
			else
			{
				++j;
				return (&environ[i]);
			}
		}
	}
	return (NULL);
}

// Function to remove/unset an environment variable
int			ft_unsetenv(const char *name)
{
	extern char	**environ;
	char		**dst;
	char		**src;
	int			tlen;

	if (!name || !*name || ft_strstr(name, "="))
		return (-1);
	else
	{
		if (!(dst = getenvvar(name)))
			return (0);
		src = dst + 1;
		tlen = ft_tablen(src);
		ft_memmove(dst, src, sizeof(char*) * tlen);
		dst[tlen] = NULL;
		return (0);
	}
}

// Function to handle the 'unset' command
int ft_unset(t_data *data, char *arguments[])
{
    int error_flag = 0;
    int word_i = 1;
    char *key;
    char *error_message;

    while (arguments[word_i] != NULL)
    {
        if (!is_proper_env(arguments[word_i]))
        {
            error_flag = 1;
            error_message = "unset: invalid argument\n";
            write(STDERR_FILENO, error_message, ft_strlen(error_message));
            word_i++;
            continue;
        }
        else
        {
            key = arguments[word_i];
            // Code to remove/unset the environment variable with 'key'
            // You need to implement this part based on your environment variable handling logic
            // For example, you can use the unsetenv() function to remove the variable.
            if (ft_unsetenv(key) != 0)
			{
                perror("unsetenv");
                error_flag = 1;
            }
            word_i++;
        }
    }
    // Set the exit code based on the error_flag
    if (error_flag)
    {
        data->exit_code = EXIT_FAILURE;
    }
    else
    {
        data->exit_code = EXIT_SUCCESS;
    }
}

/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    t_data data;
    data.exit_code = 0;

    if (argc < 2)
    {
        printf("Usage: %s <variable1> <variable2> ...\n", argv[0]);
        return 1;
    }
    ft_unset(&data, argv);

    return data.exit_code;
}
*/