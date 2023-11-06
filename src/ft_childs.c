/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:03:16 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/06 13:47:10 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_childs(t_data *l)
{
	int	i;
	int	status;

	i = 0;
	while (i < l->pipe_nb + 2)
		waitpid(l->child_pid[i++], &status, 0);
}