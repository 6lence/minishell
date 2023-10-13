/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:42:50 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/13 15:27:05 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
}

static int	valid_env_name(char *arg)
{
	int		i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
/* code 1
static void	add_or_update_env(t_data *data, char *arg)
{
	int		i;
	char	*new_env;
	char	**new_envp;

	i = -1;
	while (data->envp[++i])
		if (ft_strncmp(data->envp[i], arg, ft_strlen(arg)) == 0 && \
			data->envp[i][ft_strlen(arg)] == '=')
			return ;
	new_env = ft_strjoin(arg, "=");
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (data->envp[++i])
		new_envp[i] = ft_strdup(data->envp[i]);
	new_envp[i] = new_env;
	new_envp[i + 1] = NULL;
	free(data->envp); // Free old envp here, you might need to free its elements too
	data->envp = new_envp;
}
*/
/* code 2
static void	add_or_update_env(t_data *data, char *arg)
{
	int		i;
	char	**new_envp;

	i = -1;
    // Search for the existing environment variable
	while (data->envp[++i])
		if (ft_strncmp(data->envp[i], arg, ft_strchr(arg, '=') - arg) == 0)
		{
            // Update the value of the existing environment variable
			free(data->envp[i]);
			data->envp[i] = ft_strdup(arg);
			return ;
		}
    
    // Add a new environment variable if it doesn't exist
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (data->envp[++i])
		new_envp[i] = ft_strdup(data->envp[i]);
	new_envp[i] = ft_strdup(arg); // Add the new environment variable
	new_envp[i + 1] = NULL;
	free(data->envp); // Free old envp here, you might need to free its elements too
	data->envp = new_envp;
}
*/
int array_length(char **array)
{
    int length = 0;
    while (array[length])
    {
        length++;
    }
    return length;
}

void add_or_update_env(t_data *data, char *key, char *value)
{
    int i = 0;
    char *new_env_entry = ft_strjoin(key, "=");
    new_env_entry = ft_strjoin(new_env_entry, value);

    // Check if the key exists and update the value
    while (data->envp[i])
    {
        if (ft_strncmp(data->envp[i], key, ft_strlen(key)) == 0 && data->envp[i][ft_strlen(key)] == '=')
        {
            free(data->envp[i]); // Free the old entry
            data->envp[i] = new_env_entry; // Update with the new entry
            return;
        }
        i++;
    }

    // If key does not exist, add a new entry
    i = 0;
    char **new_envp = (char **)malloc(sizeof(char *) * (array_length(data->envp) + 2));
    int j = 0;
    while (data->envp[j])
    {
        new_envp[j] = data->envp[j];
        j++;
    }
    new_envp[j] = new_env_entry;
    new_envp[j + 1] = NULL;
    free(data->envp);
    data->envp = new_envp;
}

int	ft_export(t_data *l)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	if (!(l->arguments[1])) // If no argument after ft_export
	{
		print_envp(l->envp);
		return (0);
	}
	if (!valid_env_name(l->arguments[1]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(l->arguments[1], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (-1); //error
	}

	equal_sign = ft_strchr(l->arguments[1], '='); // find the position of '=' in the argument
	if (equal_sign) // if '=' is found
	{
		*equal_sign = '\0'; // replace '=' with '\0' to split the string
		key = l->arguments[1]; // the key is before '='
		value = equal_sign + 1; // the value is after '='
	}
	else
	{
		key = l->arguments[1]; // if '=' is not found, only the key is provided
		value = NULL; // value is NULL
	}

	add_or_update_env(l, key, value); // call add_or_update_env with data, key, and value
	return (0);
}

/*
int	ft_export(t_data *l)
{
	if (!(l->arguments[1])) // If no argument after ft_export
	{
		print_envp(l->envp);
		return (0);
	}
	if (!valid_env_name(l->arguments[1]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(l->arguments[1], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (-1); //error
	}
	add_or_update_env(l, l->arguments[1]);
	return (0);
}
*/
/*
static void free_envp(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

int main(void)
{
    t_data data;

    // Initialization of data
    data.envp = (char **)malloc(sizeof(char *) * 4); // Example environment
    if (!data.envp)
        return (1); // Handle memory allocation failure
    data.envp[0] = ft_strdup("USER=root");
    data.envp[1] = ft_strdup("HOME=/root");
    data.envp[2] = ft_strdup("SHELL=/bin/bash");
    data.envp[3] = NULL;

    // No arguments: should print the environment
    data.arguments = (char **)malloc(sizeof(char *) * 2);
    if (!data.arguments)
    {
        free_envp(data.envp);
        return (1); // Handle memory allocation failure
    }
    data.arguments[0] = ft_strdup("ft_export");
    data.arguments[1] = NULL;
    ft_export(&data);
    free(data.arguments[0]);
    free(data.arguments);

    // With valid argument: should add or update environment variable
    data.arguments = (char **)malloc(sizeof(char *) * 3);
    if (!data.arguments)
    {
        free_envp(data.envp);
        return (1); // Handle memory allocation failure
    }
    data.arguments[0] = ft_strdup("ft_export");
    data.arguments[1] = ft_strdup("PATH=/usr/local/bin");
    data.arguments[2] = NULL;
    ft_export(&data);
    free(data.arguments[0]);
    free(data.arguments[1]);
    free(data.arguments);

    // Invalid argument: should print error message
    data.arguments = (char **)malloc(sizeof(char *) * 3);
    if (!data.arguments)
    {
        free_envp(data.envp);
        return (1); // Handle memory allocation failure
    }
    data.arguments[0] = ft_strdup("ft_export");
    data.arguments[1] = ft_strdup("1INVALID=argument");
    data.arguments[2] = NULL;
    ft_export(&data);
    free(data.arguments[0]);
    free(data.arguments[1]);
    free(data.arguments);

    // Cleanup
    free_envp(data.envp);
    return (0);
}
*/
