/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:00:56 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/10 00:30:32 by mescobar         ###   ########.fr       */
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

int find_env_variable(char **envp, const char *var_name)
{
    int index;

    index = 0;
    while (envp[index] != NULL)
    {
        if (ft_strncmp(envp[index], var_name, \
                ft_strlen(var_name)) == 0 && envp[index][ft_strlen(var_name)] == '=')
        {
            return (index);
        }
        index++;
    }
    return (-1);
}

void add_env_variable(char ***envp, char *argument)
{
    int envp_len;
    char **new_envp;

    envp_len = 0;
    while ((*envp)[envp_len] != NULL)
    {
        envp_len++;
    }
    new_envp = (char **)ft_realloc(*envp, (envp_len + 2) * sizeof(char *));
//    new_envp = ft_realloc(*envp, (envp_len + 2) * sizeof(char *));
    if (!new_envp)
    {
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
    if (index != -1)
    {
        // Do not duplicate the value, just update it
//        free((*envp)[index]); //free segmentation fault
        (*envp)[index] = ft_strdup(argument);
    }
    else
    {
        add_env_variable(envp, argument);
    }
}

int	ft_cd(t_data *l)
{
    char *new_dir;
    char cwd[1024];
    char *old_pwd;
    char *new_pwd;

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
    free(old_pwd);

    // Debug prints to understand what is in the list at position l->pos
    // increment position to point to the argument of cd
    t_params *element = ft_list_elem(l->list, l->pos + 1);
    if (element) 
    {
        printf("Element at position %d: %s\n", l->pos + 1, element->str);
        new_dir = element->str;
    }
    else 
    {
        printf("Element at position %d not found.\n", l->pos + 1);
        new_dir = NULL;
    }

    if (new_dir == NULL)
    {
        printf("No directory provided, defaulting to home directory.\n");
        // You might want to set new_dir to the home directory here.
        return (-1);
    }
    
    printf("Attempting to change directory to: %s\n", new_dir); // Debug print
    
    // Change directory
    if (chdir(new_dir) == -1)
    {
        perror("cd");
        return (-1);
    }
    
    // Get the new current working directory
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("getcwd");
        return (-1);
    }
    
    // Update PWD
    new_pwd = ft_strjoin("PWD=", cwd);
    handle_env_variable(&(l->envp), "PWD", new_pwd);
    printf("PWD updated: %s\n", new_pwd); // Debug print
    free(new_pwd);
    return (0);
}
