/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:17:23 by mescobar          #+#    #+#             */
/*   Updated: 2023/02/14 09:30:29 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*scop;
	unsigned int	i;

	if (!s)
		return (NULL);
	scop = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!scop)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		scop[i] = f(i, s[i]);
		i++;
	}
	scop[i] = '\0';
	return (scop);
}
