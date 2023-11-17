/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:26:35 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/17 11:54:03 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_code(int *err_flag, t_data *l)
{
	if (err_flag == 0)
		l->exit_code = EXIT_SUCCESS;
	else
		l->exit_code = EXIT_FAILURE;
}

void	ft_is_not_proper_variable(char *key, int *error_flag)
{
	char	*err_msg;

	*error_flag = 1;
	err_msg = ft_strjoin("Error: unable to unset environment variable: ",
			key);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	free(err_msg);
}

void	ft_is_not_proper_env(t_params *element, int *error_flag)
{
	char	*err_msg;

	*error_flag = 1;
	err_msg = ft_strjoin("unset: invalid argument: ", element->str);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	free(err_msg);
}

t_params	*ft_get_nth_param(t_params *list, int n)
{
	t_params	*current;

	current = list;
	while (current && current->pos != n)
		current = current->next;
	return (current);
}
