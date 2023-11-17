/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:31:47 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/17 16:39:34 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_equal(char *str, char s)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == s)
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		printf("declare -x %s\n", str[i++]);
}

int	array_length(char **array)
{
	int	length;

	length = 0;
	while (array[length])
	{
		length++;
	}
	return (length);
}

int	valid_env_name(char *arg)
{
	int		i;

	if (!arg || arg[0] == '=')
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
