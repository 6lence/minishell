/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:09:11 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/20 10:31:25 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_2(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_wildcard(t_params *params, char **env)
{
	t_params	*tmp;
	int			i;

	(void)env;
	tmp = params;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == '*')
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_wild_in(char *str1, char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str2[i])
	{
		if (str1[j] == '*')
			j++;
		if (str2[i + j] == str1[j])
		{
			j++;
			if (j == n)
				return (1);
		}
		else
		{
			i++;
			j = 0;
		}
	}
	return (0);
}

int	ft_in_wild(char *str, char s)
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
