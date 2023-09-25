/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:33:01 by ashalagi          #+#    #+#             */
/*   Updated: 2023/07/18 07:53:20 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*p;
	size_t	i;

	i = 0;
	p = malloc(num * size);
	if (!p)
		return (NULL);
	while (i < num * size)
	{
		((unsigned char *)p)[i] = 0;
		++i;
	}
	return (p);
}
