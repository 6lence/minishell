/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:04:27 by ashalagi          #+#    #+#             */
/*   Updated: 2023/02/08 14:14:13 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	size_t	i;

	if (!destination && !source)
		return (destination);
	i = 0;
	while (i < n)
	{
		((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
		++i;
	}
	return (destination);
}
