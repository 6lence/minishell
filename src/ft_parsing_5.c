/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:21:41 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 21:16:33 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verif(char *s)
{
	int	i;
	int	ct;

	i = 0;
	while (s[i])
	{
		ct = 0;
		if (s[i] == 34)
		{
			i++;
			if (s[i] == 39)
				ct++;
			while (s[i] != 34 && ct == 0)
			{
				if (s[i] == '$')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

char	*ft_find_2(char *var, t_data *l)
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
	free(var);
	return (line);
}

char	*ft_find(t_params *list, t_data *l)
{
	int		i;
	int		var_len;
	char	*var;

	i = 0;
	while (list->str[i] != '$')
		i++;
	var_len = 0;
	while (list->str[i] != ' ')
	{
		i++;
		var_len++;
	}
	var = ft_substr(list->str, i, i + var_len);
	return (ft_find_2(var, l));
}

void	ft_change(t_params *list, t_data *l)
{
	char	*new;
	int		i;

	i = 0;
	while (list->str[i] != '$')
		i++;
	new = ft_substr(list->str, 0, i - 1);
	new = ft_strjoin(new, ft_find_var(list, l));
	free(list->str);
	list->str = new;
}

void	ft_look_dollar(t_data *l)
{
	t_params	*tmp;

	tmp = l->list;
	while (tmp)
	{
		if (ft_verif(tmp->str) == 1)
			ft_change(tmp, l);
		tmp = tmp->next;
	}
}
