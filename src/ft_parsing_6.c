/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:16:10 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/24 14:46:09 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect_output(t_params *tmp, t_data *l, char *c)
{
	l->output = open(tmp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!l->output)
		return (1);
	return (0);
}

int	ft_redirect_input(t_params *tmp, t_data *l, char *c)
{
	if (ft_strcmp(c, "<<") == 0)
	{
		pipe(l->old_fd);
		l->tmp_file = l->old_fd[1];

	}
	l->input = open(tmp->next->str, O_RDONLY, 0644);
	if (!l->input)
		return (1);
	return (0);
}

void	ft_look_in_out_put(t_data *l)
{
	char		*c;
	char		*cc;
	char		*c2;
	char		*c22;
	t_params	*tmp;

	c = "<";
	cc = "<<";
	c2 = ">";
	c22 = ">>";
	tmp = l->list;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, c) == 0 || ft_strcmp(tmp->str, cc) == 0)
		{
			if (ft_redirect_input(tmp, l, tmp->str) == 1)
				break ;
		}                                                                                                                                   
		else if (ft_strcmp(tmp->str, c2) == 0 || ft_strcmp(tmp->str, c22))
		{
			if (ft_redirect_output(tmp, l, tmp->str) == 1)
				break ;
		}
		tmp = tmp->next;
	}
}

char	*ft_find_in_env(char *var, t_data *l)
{
	int		i;
	char	*line;

	i = 0;
	while (l->envp[i])
	{
		line = ft_pathcmp(l->envp[i], var);
		if (line != NULL)
			break ;
		i++;
	}
	return (line);
}

char	*ft_find_var(t_params *list, t_data *l)
{
	int		len;
	int		i;
	int		ct;
	char	*var;
	char	*var_in_env;

	i = 0;
	while (list->str[i] != '$')
		i++;
	ct = 1;
	while (list->str[i + ct] != ' ' && list->str[i + ct] != 34
			&& (list->str[i + ct] < 7 || list->str[i + ct] > 13))
		ct++;
	var = ft_substr(list->str, i + 1, ct - 1);
	var_in_env = ft_find_in_env(var, l);
	len = ft_strlen(var) + 1;
	free(var);
	var = ft_substr(var_in_env, len, ft_strlen(var_in_env) - len);
	return (var);
}