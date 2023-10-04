/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:38:07 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/04 11:59:01 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to print environment variables
void ft_env(t_data *data)
{
    int index = 0;
    char *env_variable;

    if (data == NULL || data->envp == NULL)
    {
        write(STDERR_FILENO, "Error: data or data->envp is NULL\n", 35);
        return;
    }

    // Print all environment variables
    while (data->envp[index] != NULL)
    {
        env_variable = data->envp[index];

        if (env_variable != NULL && ft_strchr(env_variable, '='))
        {
            printf("%s\n", env_variable);
        }
        index++;
    }
}

/*
int main(void)
{
    t_data data;

    char *envp[] = {
        "USER=root",
        "HOME=/root",
        "SHELL=/bin/bash",
        NULL
    };

    data.envp = envp;
    // initialize other fields of data as necessary

    ft_env(&data);

    return 0;
}
*/