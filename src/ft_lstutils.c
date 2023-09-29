/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:22:45 by miguel            #+#    #+#             */
/*   Updated: 2023/09/29 13:22:40 by miguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_params	*ft_lstlast(t_data *l)
{
	t_params	*tmp;

	tmp = l->list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_params	*ft_lstfirst(t_data *l)
{
	t_params	*tmp;

	tmp = l->list;
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

int	ft_lstlen(t_data *l)
{
	return (ft_lstlast(l)->pos);
}
