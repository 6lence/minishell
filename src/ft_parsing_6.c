/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:16:10 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/16 14:22:30 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ajouter variable au .h

void	ft_flash_1(t_data *l)
{
	char		*c;
	t_params	*tmp;

	c = "<";
	tmp = l->list;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, c) == 0)
			ft_redirect_input(tmp, l);
		tmp = tmp->next;
	}
}