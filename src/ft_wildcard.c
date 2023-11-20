/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:27:29 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/20 10:26:44 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_verify(t_params *l, char **file_list)
{
	int			i;
	int			len;
	char		**res;
	t_params	*tmp;

	i = 0;
	len = 0;
	tmp = l;
	while (tmp && !ft_in_wild(tmp->str, '*') && !ft_operator_cmp(tmp))
		tmp = tmp->next;
	while (file_list[i])
	{
		if (ft_wild_in(tmp->str, file_list[i], ft_strlen(tmp->str)))
			len++;
		i++;
	}
	printf("ouais\n");
	printf("%d\n", len);
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
			res[len++] = file_list[i];
		i++;
	}
	return (res);
}

int	ft_file_nb(t_params	*command)
{
	DIR				*d;
	struct dirent	*dir;
	int				i;
	t_params		*tmp;

	tmp = command;
	i = 0;
	d = opendir(".");
	dir = readdir(d);
	while (tmp && !ft_in_wild(tmp->str, '*')
		&& !ft_operator_cmp(tmp))
	{
		tmp = tmp->next;
		i++;
	}
	while (dir)
	{
		if (ft_wild_in(tmp->str, dir->d_name, ft_strlen(tmp->str)))
			i++;
		dir = readdir(d);
	}
	closedir(d);
	return (i);
}

char	**execute_command_with_wildcards_loop(t_params *commands)
{
	DIR				*d;
	struct dirent	*dir;
	char			**res;
	int				i;

	i = 0;
	res = ft_calloc(ft_file_nb(commands) + 2, sizeof(char *));
	while (commands->next && !ft_in_wild(commands->next->str, '*'
			&& !ft_operator_cmp(commands->next)))
	{
		if (access(commands->str, 0) == 0 && i == 0)
			res[i++] = ft_divide_path(commands->str);
		else
			res[i++] = ft_strdup(commands->str);
		commands = commands->next;
	}
	d = opendir(".");
	dir = readdir(d);
	while (dir)
	{
		if (ft_wild_in(commands->str, dir->d_name, ft_strlen(commands->str)))
			res[i++] = ft_strdup(dir->d_name);
		dir = readdir(d);
	}
	closedir(d);
	res[i] = NULL;
	return (res);
}
