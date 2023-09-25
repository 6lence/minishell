/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:46:19 by ashalagi          #+#    #+#             */
/*   Updated: 2023/02/16 11:04:27 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int srch)
{
	char	*st;

	st = (char *)str;
	while (*st)
		st++;
	while (st >= str)
	{
		if (*st == srch)
			return (st);
		st--;
	}
	return (NULL);
}
