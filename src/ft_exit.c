/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:14:04 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/17 14:39:32 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_arguments(char **arguments)
{
	int	count;

	count = 0;
	while (arguments[count] != NULL)
	{
		count++;
	}
	return (count);
}

void	ft_arg_count(t_params *arguments, t_data *l)
{
	int	exit_code;

	arguments = arguments->next;
	exit_code = ft_atoi(arguments->str);
	if (exit_code == 0 && ft_strcmp(arguments->str, "0") != 0)
		exit(EXIT_FAILURE);
	l->exit_code = exit_code;
}

int	ft_exit(t_data *l)
{
	int			arg_count;
	t_params	*arguments;

	arguments = l->list;
	arg_count = ft_lstsize(arguments);
	if (arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (arg_count > 1)
		ft_arg_count(arguments, l);
	else
		l->exit_code = 0;
	l->stop_main = 0;
	return (0);
}
