/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:53:42 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/05 16:19:48 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verif_node(t_params *tmp, t_data *l)
{
	size_t	i;
	int		b;
	int		ct;

	b = 0;
	i = 0;
	ct = 1;
	while (tmp->str[i] && b < 2)
	{
		if ((tmp->str[i] <= 'z' && tmp->str[i] >= 'a')
			|| (tmp->str[i] <= 'Z' && tmp->str[i] >= 'A'))
			i++;
		if (tmp->str[i++] == '=')
			b++;
		if (tmp->str[i++] == 39)
			while (tmp->str[i] != 39)
				i++;
		if (tmp->str[i++] == 34)
			while (tmp->str[i] != 34)
				i++;
	}
	if (tmp->prev == NULL || ft_operator_cmp(tmp->prev))
		ft_verif_tmp_var(tmp, l, i, b);
	return (ct);
}

int	ft_in(t_params *tmp, char c)
{
	int	i;

	i = 0;
	while (tmp->str[i])
	{
		if (tmp->str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_add_var(t_data *l)
{
	t_params	*tmp;
	int			ct;

	tmp = l->list;
	ct = 0;
	while (tmp)
	{
		if (ft_in(tmp, '=') == 1)
			if (ft_verif_node(tmp, l) == 1)
				ct = 1;
		tmp = tmp->next;
	}
	return (ct);
}
