/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:00:56 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/09 14:51:11 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to print all environment variables
void	print_env_variables(char **envp)
{
	int		index;
	char	*env_variable;

	index = 0;
	while (envp[index])
	{
		env_variable = envp[index];
		if (ft_strchr(env_variable, '='))
		{
			printf("%s\n", env_variable);
		}
		index++;
	}
}

// Function to find the index of an environment variable
int	find_env_variable(char **envp, const char *var_name)
{
	int	index;

	index = 0;
	while (envp[index] != NULL)
	{
		if (ft_strncmp(envp[index], var_name, \
			ft_strlen(var_name)) == 0 && envp[index][strlen(var_name)] == '=')
		{
			return (index);
		}
		index++;
	}
	return (-1);
}

// Function to add a new environment variable
void	add_env_variable(char ***envp, char *argument)
{
	int		envp_len;
	char	**new_envp;

	envp_len = 0;
	while ((*envp)[envp_len] != NULL)
	{
		envp_len++;
	}
	new_envp = ft_realloc(*envp, (envp_len + 2) * sizeof(char *));
	if (!new_envp)
	{
		fprintf(stderr, "Memory allocation error\n"); // error exit ??? to verify
		exit(1);
	}
	new_envp[envp_len] = ft_strdup(argument);
	new_envp[envp_len + 1] = NULL;
	*envp = new_envp;
}

void	handle_env_variable(char ***envp, const char *var_name, \
		char *var_value, char *argument)
{
	int	index;

	*var_value = '\0';	// Terminate the variable name
	var_value++;		// Move to the value part
	index = find_env_variable(*envp, var_name);
	if (index != -1)
	{
        // Do not duplicate the value, just update it
		free((*envp)[index]);
		(*envp)[index] = argument;
	}
	else
	{
		add_env_variable(envp, argument);
	}
}

int	ft_cd(t_data *data)
{
	char	*new_dir;
	char	*new_pwd;
	int		index;

	new_dir = data->arguments[1];
	if (new_dir == NULL)
	{
        // If no directory is provided, go to the home directory
		index = find_env_variable(data->envp, "HOME");
		if (index != -1)
		{
			new_dir = data->envp[index] + 5; // skip "HOME="
		}
	}
	if (new_dir)
	{
		if (chdir(new_dir) == -1)
		{
			perror("cd"); // when the directory doesn't exist
			return (-1);
		}
		else
		{
			char cwd[1024]; // Update the PWD (Present Working Directory) environment variable
			getcwd(cwd, sizeof(cwd));
			new_pwd = ft_strjoin("PWD=", cwd);
			handle_env_variable(&(data->envp), "PWD", new_pwd, new_pwd);
		}
	}
	else
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

/*
int main()
{
    // Create a sample environment variable array
    char *envp[] = {
        "HOME=/home/user",
        "PWD=/home/user",
        "VAR1=value1",
        "VAR2=value2",
        "VAR3=value3",
        NULL
    };

    t_data data;
    data.params = malloc((sizeof(char *) * (sizeof(envp) / sizeof(envp[0]))) + 1);
    if (!data.params)
    {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    for (int i = 0; envp[i] != NULL; i++)
    {
        data.params[i] = ft_strdup(envp[i]);
    }
    data.params[sizeof(envp) / sizeof(envp[0])] = NULL;

    data.arguments = (char *[]){"cd", "/tmp", NULL}; // Sample cd command with a directory argument

    // Call your ft_cd function
    ft_cd(&data);

    // Print the updated environment variables (including PWD)
    print_env_variables(data.params);

    // Clean up dynamically allocated memory
    for (int i = 0; data.params[i] != NULL; i++)
    {
        free(data.params[i]);
    }
    free(data.params);

    return 0;
}
*/
