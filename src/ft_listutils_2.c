/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listutils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:30:31 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/25 13:40:00 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_params *l)
{
	int	len;

	if (!l)
		return (0);
	len = 0;
	while (l)
	{
		len++;
		l = l->next;
	}
	return (len);
}

t_params	*ft_list_elem(t_params *l, int pos)
{
	t_params	*tmp;
	int			i;

	if (!l) // Check if the list is empty
	{
		printf("Error: List is empty.\n");
		return (NULL);
	}
	tmp = l;
	i = 0;
	while (i < pos)
	{
		if (!tmp->next) // Check if next element exists
		{
			printf("Error: Position out of range.\n");
			return (NULL);
		}
		tmp = tmp->next;
		i++; // Increment the counter
	}
	return (tmp);
}
