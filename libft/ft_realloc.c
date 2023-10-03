/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:08:49 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/03 09:03:35 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr)
	{
		if (size)
		{
			if (!(new_ptr = ft_memalloc(size)))
				return (NULL);
			ft_bzero(new_ptr, size);
			ft_memcpy(new_ptr, ptr, size);
		}
		else
		{
			if (!(new_ptr = (unsigned char *)malloc(sizeof(ptr))))
				return (NULL);
		}
		free(ptr);
		return (new_ptr);
	}
	return ((unsigned char *)malloc(sizeof(ptr) * size));
}
/*
void *ft_realloc(void *ptr, size_t size)
{
    void *new_ptr;

    if (ptr)
    {
        if (size)
        {
            if (!(new_ptr = malloc(size)))
                return (NULL);
            memcpy(new_ptr, ptr, size);
        }
        else
        {
            // If size is zero, just free the old pointer and return NULL
            free(ptr);
            return (NULL);
        }
        free(ptr);
        return (new_ptr);
    }

    // If ptr is NULL, allocate memory for the new pointer
    return malloc(size);
}
*/