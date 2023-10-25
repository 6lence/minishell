/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:15:03 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/25 13:26:19 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h> // For NULL definition

int	is_proper_env(const char *env_name)
{
	int	i;

	printf("Debug: Checking env_name: %s\n", env_name);
	if (env_name == NULL || env_name[0] == '\0')
	{
		return (0); // Return false for NULL or empty strings
	}
	i = 0;
	while (env_name[i])
	{
		if (!(ft_isalnum((unsigned char)env_name[i]) || env_name[i] == '_'))
		{
			return (0); // Return false for invalid characters
		}
		i++;
	}
	return (1); // Return true for valid env variable names
}

char	**ft_getenvvar(t_data *data, const char *name)
{
	int	i;
	int	j;
	int	name_len;

	printf("Debug: Getting env var: %s\n", name);
	if (!name || !data || !data->envp)
		return (NULL);
	i = 0;
	name_len = ft_strlen(name);
	while (data->envp[i])
	{
		j = 0;
		while (name[j] && data->envp[i][j] && name[j] == data->envp[i][j])
			++j;
		if (data->envp[i][j] == '=' && j == name_len)
			return (&data->envp[i]);
		++i;
	}
	return (NULL);
}

int	ft_unsetenv(t_data *data, const char *name)
{
	char	**target;
	char	**new_envp;
	int		i;
	int		j;

	printf("Debug: Unsetting env var: %s\n", name);
	if (!name || !data || !data->envp)
		return (-1);
	target = ft_getenvvar(data, name);
	if (!target)
		return (0); // The environment variable does not exist
    i = 0; // Count the number of environment variables
	while (data->envp[i])
		++i;
	new_envp = (char **)malloc(sizeof(char *) * i); // Allocate memory for new environment array
	if (!new_envp)
		return (-1); // Memory allocation failed
    // Copy all variables except the target one
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		if (&data->envp[i] != target)
			new_envp[j++] = data->envp[i];
		++i;
	}
	new_envp[j] = NULL; // Null-terminate the new environment array
	if (data->envp_allocated) // Check if data->envp was dynamically allocated
	{
		free(data->envp); // Only free data->envp if it was dynamically allocated
		data->envp_allocated = 0; // Reset the allocation flag
	}
	data->envp = new_envp; // Assign the new environment array to data->envp
	data->envp_allocated = 1; // Set the allocation flag to true
	return (0);
}

#include "minishell.h"

// Function to retrieve the nth element in the linked list
t_params *ft_get_nth_param(t_params *list, int n) 
{
    t_params *current = list;
    while (current && current->pos != n)
    {
        current = current->next;
    }
    return current;
}

int	ft_unset(t_data *l)
{
    t_params *element;
	int	error_flag;
    int pos;

	printf("Debug: Entering ft_unset function\n");
	error_flag = 0; // Initialize error_flag to false (0)
	pos = l->pos + 1; // Adjust position based on your needs

	element = ft_get_nth_param(l->list, pos); // Get the nth element

	while (element) // Loop through each element in the linked list
	{
		printf("Debug: Processing element: %s\n", element->str); // Debug
		if (!is_proper_env(element->str)) // Check if each element is a valid environment variable name
		{
			error_flag = 1; // Set error flag to true (1)
			char *error_message = ft_strjoin("unset: invalid argument: ", element->str);
			ft_putendl_fd(error_message, STDERR_FILENO);
			free(error_message);
		}
		else
		{
			char *key = element->str; // Process valid environment variable names
			printf("Debug: Key to unset: %s\n", key);
			if (ft_unsetenv(l, key) != 0)
			{ // Check the return value of ft_unsetenv, handle error appropriately
				error_flag = 1;
				char *error_message = ft_strjoin("Error: unable to unset environment variable: ", key);
				ft_putendl_fd(error_message, STDERR_FILENO);
				free(error_message);
			}
		}
		element = element->next; // Move to the next element
	}
	
	if (error_flag == 0) // Set exit_code based on error_flag
		l->exit_code = EXIT_SUCCESS;
	else
		l->exit_code = EXIT_FAILURE;
	printf("Debug: Exiting ft_unset with code: %d\n", l->exit_code);
	return (l->exit_code); // Return the exit code
}

/*
int main(void)
{
    t_data data;
    char *args[] = {"unset", "HOME", NULL};
    char *new_env[] = {"USER=root", "HOME=/root", "SHELL=/bin/bash", NULL};
    int i;

    // Initialize t_data struct
    data.envp = new_env;
    data.arguments = args;
    data.envp_allocated = 0;

    // Testing getenvvar
    char **var = ft_getenvvar(&data, "HOME");
    if (var && *var)
        printf("Found variable: %s\n", *var);
    else
        printf("Variable not found.\n");

    // Testing ft_unsetenv
    int res = ft_unsetenv(&data, "HOME");
    if (res == 0)
    {
        printf("ft_unsetenv successful. New environment:\n");
        i = 0;
        while (data.envp[i])
        {
            printf("%s\n", data.envp[i]);
            i++;
        }
    }
    else
    {
        printf("ft_unsetenv operation failed.\n");
    }

    // Testing ft_unset
    ft_unset(&data, args);
    printf("ft_unset called. New environment:\n");
    i = 0;
    while (data.envp[i])
    {
        printf("%s\n", data.envp[i]);
        i++;
    }

    // Clean up and freeing allocated memory if needed
    // For instance, if you dynamically allocate memory for the envp array or its elements, ensure to free it appropriately.

    return 0;
}
*/