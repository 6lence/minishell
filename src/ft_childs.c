/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:03:16 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/17 15:29:47 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_childs(t_data *l)
{
	int	i;
	int	status;

	status = 0;
	if (l->commands)
	{
		i = 0;
		while (i < l->commands)
		{
			if (status)
				l->status = status;
			waitpid(l->child_pid[i++], &status, 0);
		}
	}
	else
	{
		waitpid(0, &status, 0);
		l->status = 127;
	}
}
