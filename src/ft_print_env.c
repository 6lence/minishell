/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:33:13 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/05 17:45:24 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_var_value(char *var)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (var[i] && var[i] != '=')
	{
		ct += var[i];
		i++;
	}
	return (ct);
}

void	ft_print_in_order(t_var *list, int len)
{
	t_var	*tmp;
	int		j;

	while (len > 0)
	{
		tmp = list;
		j = ft_var_value(tmp->var);
		while (tmp)
		{
			if (ft_var_value(tmp->var) < j)
				j = ft_var_value(tmp->var);
			else
			{
				printf("%s\n", tmp->var);
				free(tmp);
				tmp = tmp->next;
			}
			tmp = tmp->next;
		}
		len--;
	}
}

void	ft_print_env(char **var)
{
	int		i;
	t_var	*tmp;
	t_var	*new;

	new = malloc(sizeof(t_var));
	i = 0;
	while (var[i])
	{
		new->var = ft_strdup(var[i]);
		new->next = NULL;
		if (!tmp)
			tmp = new;
		else
			tmp->next = new;
		i++;
	}
	ft_print_in_order(tmp, i);
}
