/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:26:35 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 21:55:06 by mescobar         ###   ########.fr       */
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
