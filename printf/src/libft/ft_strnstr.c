/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 09:34:07 by mescobar          #+#    #+#             */
/*   Updated: 2023/02/09 14:22:45 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!len && (!big || !little))
		return (NULL);
	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (((char *)little)[j] == ((char *)big)[i] && i < len
			&& big[i] && little[j])
		{
			i++;
			j++;
		}
		i -= j;
		if (((char *)little)[j] == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
