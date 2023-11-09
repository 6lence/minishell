/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:35:13 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/09 21:17:21 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(void)
{
	char	*buf;
	size_t	size;

	size = 1024;
	buf = (char *)malloc(size);
	if (buf == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	if (getcwd(buf, size) == NULL)
	{
		perror("getcwd");
		free(buf);
		return (NULL);
	}
	return (buf);
}
