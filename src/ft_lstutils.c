/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:22:45 by miguel            #+#    #+#             */
/*   Updated: 2023/10/12 11:43:31 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_params	*ft_lstlast(t_params *l)
{
	t_params	*tmp;

	tmp = l;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_params	*ft_lstfirst(t_params *l)
{
	t_params	*tmp;

	tmp = l;
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

int	ft_lstlen(t_params *l)
{
	return (ft_lstlast(l)->pos + 1);
}

void	ft_lstprint(t_params *l)
{
	t_params	*tmp;

	tmp = l;
	while (tmp->pos > 0)
		tmp = tmp->prev;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

t_params	*ft_lst_elem(t_params *l, int pos)
{
	t_params	*tmp;
	int			i;

	i = 0;
	tmp = l;
	while (i < pos)
		tmp = tmp->prev;
	while (i > pos)
		tmp = tmp->next;
	return (tmp);
}
