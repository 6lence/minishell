/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsrch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:58:22 by mescobar          #+#    #+#             */
/*   Updated: 2023/08/31 11:58:44 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strsrch(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s2[i])
	{
		j = 0;
		if (s2[i] == s1[j])
		{
			i++;
			j++;
		}
		if (j == ft_strlen(s1))
			return (1);
		else
			i++;
	}
	return (0);
}
