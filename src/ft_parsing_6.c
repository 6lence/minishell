/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:27:17 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 15:23:32 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_output_more(t_params *tmp, char *ct, t_data *l)
{
	if (ft_strcmp(ct, ">") == 0)
		ft_open_simple_out(tmp, ct, l);
	else if (ft_strcmp(ct, ">>") == 0)
		ft_open_double_out(tmp, ct, l);
}

void	ft_output(t_params *list, t_data *l)
{
	char	*ct;

	ct = NULL;
	if (ft_strcmp(list->str, ">") == 0)
		ct = ">";
	else if (ft_strcmp(list->str, ">>") == 0)
		ct = ">>";
	ft_output_more(list, ct, l);
}

void	ft_look_out_put(t_params *tmp, t_data *l)
{
	t_params	*copy;

	copy = tmp;
	while (copy->next && !ft_operator_cmp(copy))
		copy = copy->next;
	if (ft_strcmp(copy->str, ">") == 0
		|| ft_strcmp(copy->str, ">>") == 0)
		ft_output(copy, l);
}
