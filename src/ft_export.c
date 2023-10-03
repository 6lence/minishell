/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:42:50 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/03 09:37:15 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <ctype.h>

// Define constants for true and false
#define TRUE 1
#define FALSE 0

// Function to check if a string is a valid environment variable name
int is_valid_env_variable(const char *str)
{
    // Check if the string is empty or starts with a digit
    if (str == NULL || !ft_isalpha(str[0]))
    {
        return FALSE;
    }

    // Check if the string contains only valid characters
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
        {
            return FALSE;
        }
    }

    return TRUE;
}

// Function to print all environment variables
void print_env_variables(char **envp)
{
    int index = 0;

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
void add_env_variable(char ***envp, char *argument)
{
    int envp_len = 0;

    while ((*envp)[envp_len] != NULL)
    {
        envp_len++;
    }

    char **new_envp = ft_realloc(*envp, (envp_len + 2) * sizeof(char *));
    if (!new_envp)
    {
        // Handle memory allocation error
        fprintf(stderr, "Memory allocation error\n"); 
        exit(1);
    }

    new_envp[envp_len] = ft_strdup(argument);
    new_envp[envp_len + 1] = NULL;
    *envp = new_envp;
}

// Function to handle the 'export' command
void ft_export(t_data *data)
{
    int i;

    i = 1;
    while (data->arguments[i] != NULL)
    {
        char *arg = data->arguments[i];
        char *var_name = arg;
        char *var_value = ft_strchr(arg, '=');

        if (var_value != NULL)
        {
            *var_value = '\0'; // Terminate the variable name
            var_value++;       // Move to the value part
        }

        if (is_valid_env_variable(arg))
        {
            int index = find_env_variable(data->envp, var_name);

            if (index != -1)
            {
                free(data->envp[index]); // Free the old environment variable value
                data->envp[index] = ft_strdup(arg); // Update the environment variable
            }
            else
            {
                add_env_variable(&(data->envp), arg); // Add the new environment variable
            }
        }
        else
        {
            // Print an error message for invalid environment variable
            fprintf(stderr, "export: not a valid identifier: %s\n", arg);
        }

        i++;
    }
}


/*
void remove_env_variable(char **envp, int index);

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

void unset_env_variable(char ***envp, const char *var_name)
{
    int index = find_env_variable(*envp, var_name);

    if (index != -1)
    {
        free((*envp)[index]); // Free the memory of the environment variable
        // Shift elements in the array to fill the gap
        while ((*envp)[index + 1] != NULL)
        {
            (*envp)[index] = (*envp)[index + 1];
            index++;
        }
        (*envp)[index] = NULL; // Mark the end of the array
    }
}


// Function to add a new environment variable
void add_env_variable(char ***envp, char *argument)
{
    int envp_len = 0;

    while ((*envp)[envp_len] != NULL)
    {
        envp_len++;
    }

    char **new_envp = ft_realloc(*envp, (envp_len + 2) * sizeof(char *));
    if (!new_envp)
    {
        // Handle memory allocation error
        fprintf(stderr, "Memory allocation error\n"); 
        exit(1);
    }

    new_envp[envp_len] = ft_strdup(argument);
    new_envp[envp_len + 1] = NULL;
    *envp = new_envp;
}

// Function to print all environment variables
void print_env_variables(char **envp)
{
    int index = 0;

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
void remove_env_variable(char **envp, int index)
{
    free(envp[index]);

    // Shift elements in the array to fill the gap
    while (envp[index + 1] != NULL)
    {
        envp[index] = envp[index + 1];
        index++;
    }

    envp[index] = NULL; // Mark the end of the array
}

// Function to add or update an environment variable
void handle_env_variable(char ***envp, const char *var_name, char *var_value, char *argument)
{
    int index;
    *var_value = '\0'; // Terminate the variable name
    var_value++;       // Move to the value part
    index = find_env_variable(*envp, var_name);

    if (index != -1)
    {
        free((*envp)[index]);
//        (*envp)[index] = argument;
        (*envp)[index] = ft_strdup(argument);
    }
    else
    {
        add_env_variable(envp, argument);
    }
}

void ft_export(t_data *data)
{
    int i;
    char *var_name;
    char *var_value;

    i = 1;
    if (data->arguments[1] == NULL)
    {
        // If no arguments are provided, print all environment variables
        print_env_variables(data->envp);
    }
    else
    {
        while (data->arguments[i] != NULL)
        {
            var_name = ft_strdup(data->arguments[i]);
            var_value = ft_strchr(var_name, '=');
            if (var_value == NULL)
            {
                // Handle the unset command
                unset_env_variable(&data->envp, var_name);
            }
            else
            {
                // Handle adding or updating a variable
                handle_env_variable(&(data->envp), var_name, var_value, data->arguments[i]);
            }
            free(var_name); // Free the allocated memory
            i++;
        }
    }
}
*/


int main()
{
    // Create a sample environment variable array
    char *envp[] = {
        "VAR1=value1",
        "VAR2=value2",
        "VAR3=value3",
        NULL
    };

    // Initialize your data structure
    t_data data;
    data.envp = envp; // Use the envp field for your environment variables
    data.arguments = (char *[]){"export", "VAR4=newvalue", "VAR5=", NULL}; // Sample arguments

    // Call your ft_export function
    ft_export(&data);

    // Print the updated environment variables
    printf("Updated environment variables:\n");
    for (int i = 0; data.envp[i] != NULL; i++) {
        printf("%s\n", data.envp[i]);
    }

    return 0;
}