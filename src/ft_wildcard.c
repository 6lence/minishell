/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:27:29 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/17 14:32:45 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_wildcard(t_params *params, char **env)
{
	t_params	*tmp;
	int			i;

	(void)env;
	tmp = params;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == '*')
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_wild_in(char *str1, char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str2[i])
	{
		if (str1[j] == '*')
			j++;
		if (str2[i + j] == str1[j])
		{
			j++;
			if (j == n)
				return (1);
		}
		else
		{
			i++;
			j = 0;
		}
	}
	return (0);
}

int	ft_in_wild(char *str, char s)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	**ft_verify(t_params *l, char **file_list)
{
	int		i;
	int		len;
	char	**res;
	t_params	*tmp;

	i = 0;
	len = 0;
	tmp = l;
	while (tmp && !ft_in_wild(tmp->str, '*'))
		tmp = tmp->next;
	while (file_list[i])
	{
		if (ft_wild_in(tmp->str, file_list[i], ft_strlen(tmp->str)))
			len++;
		i++;
	}
	res = ft_calloc(sizeof(char *), len + ft_res_len(l));
	i = 0;
	len = 0;
	while (l && !ft_in_wild(l->str, '*') && !ft_operator_cmp(l))
	{
		if (access(l->str, 0) == 0 && len == 0)
			res[len++] = ft_divide_path(l->str);
		else
			res[len++] = ft_strdup(l->str);
		l = l->next;
	}
	i = 0;
	while (file_list[i])
	{
		if (ft_wild_in(tmp->str, file_list[i], ft_strlen(tmp->str)))
			res[len++] = ft_strdup(file_list[i]);
		free(file_list[i]);
		i++;
	}
	free(file_list);
	return (res);
}

char	**execute_command_with_wildcards_loop(t_params *commands)
{
	DIR *d = opendir(".");
	if (d == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}

	char **file_list = NULL;
	int file_count = 0;
	struct dirent *dir;
	dir = readdir(d);
	while (dir != NULL)
	{
		file_list = ft_realloc(file_list, sizeof(char *) * (file_count + 1));
		file_list[file_count++] = ft_strdup(dir->d_name);
		dir = readdir(d);
	}
	closedir(d);
	file_list = ft_verify(commands, file_list);
	return (file_list);
}

int	ft_in_2(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
