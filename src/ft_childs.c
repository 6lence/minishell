/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:03:16 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/10 00:30:37 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_childs(t_data *l)
{
	int	i;
	int	status;

	i = 0;
	while (i < l->commands)
		waitpid(l->child_pid[i++], &status, 0);
}
