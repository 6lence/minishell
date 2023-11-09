/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:10:15 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/09 11:42:03 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function to handle the -n option
static size_t	check_n(char **args)
{
	size_t	i;
	size_t	j;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j++] == '-' && args[i][j] && args[i][j] == 'n')
		{
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] && args[i][j] != 'n')
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	ft_operator_cmp_args(char *str)
{
	if (ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "|") == 0
		|| ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "&&") == 0)
		return (1);
	return (0);
}

void	ft_print_argument(char *str, t_data *l)
{
	int	i;

	(void)*l;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				printf("%c", str[i++]);
		}
		else if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
				printf("%c", str[i++]);
		}
		else
			printf("%c", str[i++]);
	}
}

int	ft_echo(t_data *l)
{
	int	newline;
	int	i;

	if (!l || !l->arguments)
	{
		ft_putstr_fd("Error: missing data or arguments\n", 2);
		return (-1);
	}
	i = check_n(l->arguments);
	newline = (i == 0 || ft_strcmp(l->arguments[0], "-n") != 0);
	while (l->arguments[i] && !ft_operator_cmp_args(l->arguments[i]))
	{
		ft_print_argument(l->arguments[i], l);
		if (l->arguments[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
