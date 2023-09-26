/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:42:50 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/26 11:56:39 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

#include "../src/minishell.h"

// Function to print all environment variables
void print_env_variables(char **envp)
{
    int index;

    index = 0;
    while (envp[index] != NULL)
    {
        char *env_variable = envp[index];

        if (ft_strchr(env_variable, '='))
        {
            printf("%s\n", env_variable);
        }
        index++;
    }
}

// Function to remove an environment variable by shifting the array
void remove_env_variable(char **envp, int index)
{
    free(envp[index]);

    while (envp[index] != NULL)
    {
        envp[index] = envp[index + 1];
        index++;
    }
}

// Function to unset an environment variable
void unset_env_variable(char **envp, const char *var_name)
{
    int index;
    
    index = find_env_variable(envp, var_name);
    if (index != -1)
    {
        remove_env_variable(envp, index);
    }
}

// Function to update an existing environment variable
void update_env_variable(char **envp, int index, const char *new_value)
{
    free(envp[index]);
    envp[index] = strdup(new_value);
}

// Function to add or update an environment variable
void handle_env_variable(char **envp, const char *var_name, char *var_value, char *argument)
{
    int index;
    *var_value = '\0'; // Terminate the variable name
    
    var_value++;       // Move to the value part
    index = find_env_variable(envp, var_name);
    if (index != -1)
    {
        update_env_variable(envp, index, argument);
    }
    else
    {
        add_env_variable(envp, argument);
    }
}

// Function to handle the 'export' command
void ft_export(t_data *data)
{
    int     i = 1;
    char    *var_name;
    char    *var_value;

    if (data->arguments[1] == NULL)
    {
        // If no arguments are provided, print all environment variables
        print_env_variables(data->params);
    }
    else
    {
        while (data->arguments[i] != NULL)
        {
            var_name = data->arguments[i];
            var_value = ft_strchr(var_name, '=');
            if (var_value == NULL)
            {
                // Handle the unset command
                unset_env_variable(data->params, var_name);
            }
            else
            {
                // Handle adding or updating a variable
                handle_env_variable(data->params, var_name, var_value, data->arguments[i]);
            }
            i++;
        }
    }
}







// Function to find the index of an environment variable
int find_env_variable(char **envp, const char *var_name)
{
    int index = 0;

    while (envp[index] != NULL)
    {
        if (ft_strncmp(envp[index], var_name, ft_strlen(var_name)) == 0 && envp[index][strlen(var_name)] == '=')
        {
            return index;
        }
        index++;
    }
    return -1;
}



// Function to add a new environment variable
void add_env_variable(char **envp, char *argument)
{
    int envp_len = 0;

    while (envp[envp_len] != NULL)
    {
        envp_len++;
    }

    envp = ft_realloc(envp, (envp_len + 2) * sizeof(char *));
    envp[envp_len] = ft_strdup(argument);
    envp[envp_len + 1] = NULL;
}









// Function to search for an environment variable in envp and return its index
int find_env_variable(char **envp, const char *var_name)
{
    int index;

    index = 0;
    while (envp[index] != NULL)
    {
        if (ft_strncmp(envp[index], var_name, ft_strlen(var_name)) == 0 && envp[index][strlen(var_name)] == '=')
        {
            return index;
        }
        index++;
    }
    return -1;
}

// Function to remove an environment variable
void remove_env_variable(char **envp, int index)
{
    free(envp[index]);
    while (envp[index] != NULL)
    {
        envp[index] = envp[index + 1];
        index++;
    }
}



// Function to add a new environment variable
void add_env_variable(char ***envp, const char *new_var)
{
    int envp_len = 0;
    while ((*envp)[envp_len] != NULL)
    {
        envp_len++;
    }
    *envp = ft_realloc(*envp, (envp_len + 2) * sizeof(char *));
    (*envp)[envp_len] = strdup(new_var);
    (*envp)[envp_len + 1] = NULL;
}

// Function to handle the ft_export command
void ft_export(t_data *data)
{
    int i;
    int index;
    int envp_len;

	i = 1;
    if (data->arguments[1] == NULL)
    {
        // If no arguments are provided, print all environment variables
        index = 0;
        while (data->params[index] != NULL)
        {
            printf("%s\n", data->params[index]);
            index++;
        }
    }
    else
    {
        while (data->arguments[i] != NULL)
        {
            char *var_name = data->arguments[i];
            char *var_value = ft_strchr(var_name, '=');

            if (var_value == NULL)
            {
                // Handle the unset command
                index = find_env_variable(data->params, var_name);
                if (index != -1)
                {
                    remove_env_variable(data->params, index);
                }
            }
            else
            {
                // Handle adding or updating a variable
                *var_value = '\0'; // Terminate the variable name
                var_value++;       // Move to the value part
                index = find_env_variable(data->params, var_name);

                if (index != -1)
                {
                    update_env_variable(data->params, index, data->arguments[i]);
                }
                else
                {
                    envp_len = 0;
                    while (data->params[envp_len] != NULL)
                    {
                        envp_len++;
                    }
                    data->params = ft_realloc(data->params, (envp_len + 2) * sizeof(char *));
                    data->params[envp_len] = ft_strdup(data->arguments[i]);
                    data->params[envp_len + 1] = NULL;
                }
            }
            i++;
        }
    }
}

