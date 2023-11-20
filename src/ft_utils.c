/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:53:01 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/20 15:14:15 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*save;

	save = s1;
	s1 += ft_strlen(s1);
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
	return (save);
}

char	**strrdup(char **strr)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_tablen(strr) + 1));
	i = 0;
	while (strr[i])
	{
		res[i] = ft_strdup(strr[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
