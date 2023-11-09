/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:38:07 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/10 00:30:22 by mescobar         ###   ########.fr       */
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
		printf("Error: data or data->envp is NULL\n");
		return (-1);
	}
	while (l->envp[index] != NULL)
	{
		env_variable = l->envp[index];
		if (env_variable != NULL && ft_strchr(env_variable, '='))
			printf("%s\n", env_variable);
		index++;
	}
	return (0);
}
