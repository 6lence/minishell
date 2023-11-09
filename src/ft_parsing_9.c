/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:40:07 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 15:06:26 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_simple_out(t_params *tmp, char *ct, t_data *l)
{
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_operator_cmp(tmp) && ft_strcmp(tmp->str, ct) != 0)
			break ;
		else if (ft_operator_cmp(tmp))
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		else
		{
			l->tmp_out = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (tmp->next)
				tmp = tmp->next;
			else
				break ;
		}
	}
}

void	ft_open_double_out(t_params *tmp, char *ct, t_data *l)
{
	while (tmp)
	{
		if (ft_operator_cmp(tmp) && ft_strcmp(tmp->str, ct) != 0)
			break ;
		else if (ft_operator_cmp(tmp))
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		else
		{
			l->tmp_out = open(tmp->str,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (tmp->next)
				tmp = tmp->next;
			else
				break ;
		}
	}
}
