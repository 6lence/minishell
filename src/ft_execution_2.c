/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:16:21 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/17 10:20:40 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_command(char **path, char *command)
{
	int		i;
	char	*res;
	char	*join;

	i = 0;
	res = NULL;
	while (path[i])
	{
		join = ft_strjoin(path[i], command);
		if (access(join, 0) == 0)
			res = join;
		free(path[i]);
		i++;
	}
	free(command);
	free(join);
	return (res);
}

char	*ft_access_verif(t_data *l, t_params *params)
{
	t_params	*tmp;
	char		**path;
	char		*command;

	tmp = params;
	if (access(tmp->str, 0) == 0)
		return (tmp->str);
	path = ft_search_path("PATH", l);
	command = ft_strjoin("/", tmp->str);
	return (ft_join_command(path, command));
}

int	ft_res_len(t_params *params)
{
	int			i;
	t_params	*tmp;

	i = 0;
	tmp = params;
	while (tmp && !ft_operator_cmp(tmp))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*ft_divide_path(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	return (ft_substr(str, i, ft_strlen(str)));
}

char	**ft_arguments(t_params *params, t_data *l)
{
	t_params	*tmp;
	char		**res;
	int			k;

	tmp = params;
	(void)l;
	if (ft_is_wildcard(tmp, l->envp))
		return (execute_command_with_wildcards_loop(tmp));
	res = ft_calloc(ft_res_len(params) + 1, sizeof(char *));
	k = 0;
	while (tmp && !ft_operator_cmp(tmp))
	{
		if (access(tmp->str, 0) == 0 && k == 0)
			res[k++] = ft_divide_path(tmp->str);
		else
			res[k++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	return (res);
}
