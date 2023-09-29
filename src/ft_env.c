/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:38:07 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/27 17:00:18 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

// Function to print environment variables
void ft_env(t_data *data)
{
    int index = 0;

    // Print all environment variables
    while (data->params[index] != NULL)
    {
        char *env_variable = data->params[index];

        if (ft_strchr(env_variable, '='))
        {
            printf("%s\n", env_variable);
        }
        index++;
    }
}

/*
#include <stdio.h> 

int main()
{
    t_data data;
    data.params = (char *[]){"PATH=/usr/bin", "USER=john", "HOME=/home/john", NULL}; 

    ft_env(&data);

    return 0;
}
*/