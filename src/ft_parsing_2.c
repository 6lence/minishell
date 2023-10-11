/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:29:54 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/10 15:42:03 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathcmp(char *str, char *path)
{
	size_t	i;

	i = 0;
	while (str[i] == path[i])
		i++;
	if (i == ft_strlen(path) && i - ft_strlen(path) == 0)
		return (str);
	return (NULL);
}

char	**ft_search_path(t_data *l)
{
	int		i;
	char	**tmp;
	char	*line;

	i = 0;
	while (l->envp[i])
	{
		line = ft_pathcmp(l->envp[i], "PATH");
		if (line != NULL)
			break ;
		i++;
	}
	tmp = ft_split(line, ':');
	return (tmp);
}
