/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:29:53 by ashalagi          #+#    #+#             */
/*   Updated: 2023/02/08 13:30:05 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	size_t	i;

	if (!destination && !source)
		return (destination);
	if (source < destination)
	{
		i = n;
		while (i > 0)
		{
			--i;
			((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
			++i;
		}
	}
	return (destination);
}
