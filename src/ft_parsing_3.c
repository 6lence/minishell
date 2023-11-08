/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:01:17 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/08 14:11:22 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quotes(t_data *l, int *i, int c)
{
	*i = *i + 1;
	while (l->params[*i] != c)
		*i = *i + 1;
}

int	ft_words(t_data *l)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (l->params[i])
	{
		while (l->params[i] && (l->params[i] < 7 
				|| l->params[i] > 13) && l->params[i] != ' ')
		{
			if (l->params[i] == ')' || l->params[i] == '(')
			{
				words++;
				i++;
			}
			if (l->params[i] == 34)
				ft_quotes(l, &i, 34);
			else if (l->params[i] == 39)
				ft_quotes(l, &i, 39);
			i++;
		}
		words++;
		while (l->params[i] && !((l->params[i] < 7 
					|| l->params[i] > 13) && l->params[i] != ' '))
		{
			if (l->params[i] == ')' || l->params[i] == '(')
			{
				words++;
				i++;
			}
			i++;
		}
	}
	return (words);
}

int	ft_operator_cmp(t_params *tmp)
{
	if (ft_strcmp(tmp->str, "<") == 0
		|| ft_strcmp(tmp->str, "<<") == 0
		|| ft_strcmp(tmp->str, ">") == 0
		|| ft_strcmp(tmp->str, ">>") == 0
		|| ft_strcmp(tmp->str, "|") == 0)
		return (1);
	return (0);
}

int	ft_join_access(char **path, char *command)
{
	int		i;
	char	*join;
	int		res;

	i = 0;
	res = 0;
	while(path[i])
	{
		join = ft_strjoin(path[i], command);
		if (access(join, 0) == 0)
			res = 1;
		free(join);
		free(path[i]);
		i++;
	}
	free(path);
	free(command);
	return(res);
}

int	ft_access(t_params *params, t_data *l)
{
	char	**path;
	char	*command;

	if (access(params->str, 0) == 0)
		return (1);
	path = ft_search_path("PATH", l);
	command = ft_strjoin("/", params->str);
	return (ft_join_access(path, command));
}

int	ft_count_command(t_data *l)
{
	t_params	*tmp;
	int			res;

	tmp = l->list;
	res = 0;
	while (tmp)
	{
		if (ft_access(tmp, l) == 1)
			res++;
		while (tmp->next && !ft_operator_cmp(tmp))
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (res);
}
