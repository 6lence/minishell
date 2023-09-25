/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:00:02 by ashalagi          #+#    #+#             */
/*   Updated: 2023/02/16 10:43:39 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	while (*str)
	{
		if (ch == *str)
			return ((char *)str);
		str++;
	}
	if (*str == ch)
		return ((char *)str);
	return (NULL);
}
