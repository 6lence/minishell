/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:00:56 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/13 14:10:39 by ashalagi         ###   ########.fr       */
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

int find_env_variable(char **envp, const char *var_name) {
    int index = 0;

    while (envp[index] != NULL) {
        if (ft_strncmp(envp[index], var_name, ft_strlen(var_name)) == 0 && envp[index][ft_strlen(var_name)] == '=') {
            return (index);
        }
        index++;
    }
    return (-1);
}

/*
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
*/
void add_env_variable(char ***envp, char *argument)
{
    int envp_len;
    char **new_envp;

    envp_len = 0;
    while ((*envp)[envp_len] != NULL) {
        envp_len++;
    }
    new_envp = (char **)realloc(*envp, (envp_len + 2) * sizeof(char *));
    if (!new_envp) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    new_envp[envp_len] = ft_strdup(argument);
    new_envp[envp_len + 1] = NULL;
    *envp = new_envp;
}

void handle_env_variable(char ***envp, const char *var_name, char *argument)
{
    int index;

    index = find_env_variable(*envp, var_name);
    if (index != -1) {
        // Do not duplicate the value, just update it
    //    free((*envp)[index]); free segmentation fault
        (*envp)[index] = ft_strdup(argument);
    } else {
        add_env_variable(envp, argument);
    }
}


/*
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
		(*envp)[index] = ft_strdup(argument);
	}
	else
	{
		add_env_variable(envp, argument);
	}
}
*/
#include "minishell.h"

int	ft_cd(t_data *l)
{
    char *new_dir;
    char cwd[1024];
    char *old_pwd;
    char *new_pwd;
    int index;

    // Get the current working directory
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("getcwd");
        return (-1);
    }
    // Update the OLDPWD environment variable
    old_pwd = ft_strjoin("OLDPWD=", cwd);
    handle_env_variable(&(l->envp), "OLDPWD", old_pwd);
    printf("OLDPWD updated: %s\n", old_pwd); // Debug print
    new_dir = l->arguments[1];
    if (new_dir == NULL)
    {
        // Change to the HOME directory if no argument is provided
        index = find_env_variable(l->envp, "HOME");
        if (index != -1)
        {
            new_dir = l->envp[index] + 5; // Skip "HOME="
        }
    }
    if (new_dir)
    {
        if (chdir(new_dir) == -1)
        {
            // Print an error if the directory change fails
            perror("cd");
            free(old_pwd);
            return (-1);
        }
    }
    else
    {
        ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
        free(old_pwd);
        return (-1);
    }
    // Get and update the new current working directory
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("getcwd");
        return (-1);
    }

    new_pwd = ft_strjoin("PWD=", cwd);
    printf("PWD updated: %s\n", new_pwd); // Debug print

    handle_env_variable(&(l->envp), "PWD", new_pwd);
    free(old_pwd);
    free(new_pwd); // Ensure you free the memory allocated by ft_strjoin

    return (0);
}



/*
int	ft_cd(t_data *l)
{
	char	*new_dir;
	char	*new_pwd;
	int		index;

	new_dir = l->arguments[1];
	if (new_dir == NULL)
	{
        // If no directory is provided, go to the home directory
		index = find_env_variable(l->envp, "HOME");
		if (index != -1)
		{
			new_dir = l->envp[index] + 5; // skip "HOME="
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
			handle_env_variable(&(l->envp), "PWD", new_pwd, new_pwd);
		}
	}
	else
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}
*/

/*
int main()
{
    char *envp[] =
	{
        "HOME=/home/user",
        "PWD=/home/user",
        "VAR1=value1",
        "VAR2=value2",
        "VAR3=value3",
        NULL
    };

    t_data data;
    
    // Calculate the number of environment variables
    int env_count = 0;
    while (envp[env_count] != NULL)
	{
        env_count++;
    }
    
    // Allocate memory for the environment variables in data
    data.envp = malloc(sizeof(char *) * (env_count + 1));
    if (!data.envp)
	{
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    // Copy the environment variables to data
    for (int i = 0; i < env_count; i++)
	{
        data.envp[i] = ft_strdup(envp[i]);
        if (!data.envp[i])
		{ // Check for allocation errors
            fprintf(stderr, "Memory allocation error\n");
            return 1;
        }
    }
    data.envp[env_count] = NULL; // Null-terminate the array

    // Test arguments for the cd command
    data.arguments = (char *[]){"cd", "/tmp", NULL};

    // Execute the cd command
    ft_cd(&data);

    // Print the updated environment variables
    print_env_variables(data.envp);

    // Clean up
    for (int i = 0; data.envp[i] != NULL; i++)
	{
        free(data.envp[i]);
    }
    free(data.envp);

    return 0;
}
*/