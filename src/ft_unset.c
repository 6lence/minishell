/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:15:03 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/09 15:43:46 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h> // For NULL definition

int	is_proper_env(const char *env_name)
{
	int	i;

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

int	ft_unset(t_data *data, char *arguments[])
{
	int		error_flag;
	int		word_i;
	char	*key;
	char	*error_message;

	error_flag = 0; // Initialize error_flag to false (0)
	word_i = 1; // Start with the first argument
	if (!arguments) // Ensure arguments is not NULL before dereferencing
		return (-1); // Handle error appropriately; for now, simply return or set the error_flag and error_message as needed
	while (arguments[word_i] != NULL)
	{
		if (!is_proper_env(arguments[word_i])) // Check if each argument is a valid environment variable name
		{
			error_flag = 1; // Set error flag to true (1)
			error_message = "unset: invalid argument\n";
			write(STDERR_FILENO, error_message, ft_strlen(error_message));
		}
		else
		{
			key = arguments[word_i]; // Process valid environment variable names
			if (ft_unsetenv(data, key) != 0)
			{ // Check the return value of ft_unsetenv, handle error appropriately; for now, set error_flag and print an error message
				error_flag = 1;
				error_message = "Error: unable to unset environment variable\n";
				write(STDERR_FILENO, error_message, ft_strlen(error_message));
			}
		}
		word_i++; // Move to the next argument
	}
	if (error_flag == 0) // Set exit_code based on error_flag
		data->exit_code = EXIT_SUCCESS;
	else
		data->exit_code = EXIT_FAILURE;
	return (data->exit_code); // Return the exit code
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
