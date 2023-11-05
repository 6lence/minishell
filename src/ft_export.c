/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:42:50 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/05 17:44:36 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_env_name(char *arg)
{
	int		i;

	// Check if the argument is NULL or starts with '='
	if (!arg || arg[0] == '=')
		return (0);
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

int	array_length(char **array)
{
	int length = 0;
	while (array[length])
	{
		length++;
	}
	return length;
}

int add_or_update_env(t_data *data, char *key, char *value)
{
	int i = 0;
	char *new_env_entry = ft_strjoin(key, "=");
	if (value) // Check if value is not NULL before concatenating
	{
		char *tmp = new_env_entry;
		new_env_entry = ft_strjoin(new_env_entry, value);
		free(tmp); // Ensure previously allocated memory is freed to prevent memory leaks
	}

	// Check if the key exists and update the value
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, ft_strlen(key)) == 0 && data->envp[i][ft_strlen(key)] == '=')
		{
			free(data->envp[i]); // Free the old entry
			data->envp[i] = new_env_entry; // Update with the new entry
			return (0);
		}
		i++;
	}

	// If key does not exist, add a new entry
	i = 0;
	char **new_envp = (char **)malloc(sizeof(char *) * (array_length(data->envp) + 2));
	if (!new_envp) // Check for malloc failure
	{
		return -1; // return -1 on failure
	}
	int j = 0;
	while (data->envp[j])
	{
		new_envp[j] = data->envp[j];
		j++;
	}
	new_envp[j] = new_env_entry;
	new_envp[j + 1] = NULL;
	data->envp = new_envp;
	return (0);
}


int ft_export(t_data *l)
{
	t_params *element;
	char *key;
	char *value;
	char *equal_sign;
	int pos;

	pos = l->pos + 1;
	// Check if the position is valid before accessing the element
	if (pos >= ft_lstsize(l->list)) // Assuming ft_lstsize gives the number of elements
	{
		ft_print_env(l->envp); // Print the environment variables if position is out of range
		return (0);
	}
	element = ft_list_elem(l->list, pos); // Access element at position pos

	// 1: No arguments passed, just print the environment variables
	if (!element) 
	{
		ft_print_env(l->envp);
		return (0);
	}

	// 2: Arguments passed, trying to export or update environment variables
	if (!valid_env_name(element->str))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(element->str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (-1); // error
	}
	equal_sign = ft_strchr(element->str, '='); // find the position of '=' in the argument
	if (equal_sign) // if '=' is found
	{
		*equal_sign = '\0'; // replace '=' with '\0' to split the string
		key = element->str; // the key is before '='
		value = equal_sign + 1; // the value is after '='
	}
	else
	{
		key = element->str; // if '=' is not found, only the key is provided
		value = NULL; // value is NULL
	}

	// Validate the key here after extraction
	if (!valid_env_name(key)) // Checking validity after getting the key
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(key ? key : "", 2); // handle NULL key
		ft_putendl_fd("': not a valid identifier", 2);
		return (-1); // error
	}

	// Attempt to add or update the environment variable and handle the status
	int status = add_or_update_env(l, key, value);
	if (status != 0)
	{
		printf ("Error status");
	}
	return (0);
}

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
