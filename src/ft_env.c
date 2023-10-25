/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:38:07 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/25 12:44:50 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to print environment variables
int	ft_env(t_data *l)
{
	int		index;
	char	*env_variable;

	index = 0;
	if (l == NULL || l->envp == NULL)
	{
		write(STDERR_FILENO, "Error: data or data->envp is NULL\n", 35);
		return (-1);
	}
    // Print all environment variables
	while (l->envp[index] != NULL)
	{
		env_variable = l->envp[index];
		if (env_variable != NULL && ft_strchr(env_variable, '='))
		{
			printf("%s\n", env_variable);
		}
		index++;
	}
	return (0);
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
