/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:53:42 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/26 17:38:04 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print(char *str, int len)
{
	int	i;

	printf("minishell: ");
	i = 0;
	while (i < len)
		printf("%c", str[i++]);
	printf(": command not found\n");
}

void	ft_add_to_env(t_params *tmp, t_data *l)
{
	t_var	*new;
	t_var	*tmp_var;

	new = malloc(sizeof(t_var));
	if (!new)
	{
		perror("malloc error: ");
		return ;
	}
	new->var = ft_substr(tmp->str, 0, ft_strlen(tmp->str));
	new->next = NULL;
	if (l->var)
	{
		tmp_var = l->var;
		while (tmp_var->next)
			tmp_var = tmp_var->next;
		tmp_var->next = new;
	}
	else
		l->var = new;
}

int	ft_verif_node(t_params *tmp, t_data *l)
{
	size_t	i;
	int		b;

	i = 0;
	b = 0;
	while (tmp->str[i] && b < 2)
	{
		while (((tmp->str[i] <= 'z' && tmp->str[i] >= 'a')
			|| (tmp->str[i] <= 'Z' && tmp->str[i] >= 'A')
			|| tmp->str[i] == '='))
			i++;
		if (tmp->str[i] == '=')
			b++;
		if (tmp->str[i] == 39)
		{
			i++;
			while (tmp->str[i] != 39)
				i++;
		}
		if (tmp->str[i] == 34)
		{
			i++;
			while (tmp->str[i] != 34)
				i++;
		}
		i++;
	}
	if (i != ft_strlen(tmp->str) || b > 1)
	{
		ft_print(tmp->str, i);
		return (0);
	}
	else
	{
		ft_add_to_env(tmp, l);
		return (1);
	}
}

	
int		ft_in(t_params *tmp, char c)
{
	int	i;

	i = 0;
	while (tmp->str[i])
	{
		if (tmp->str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_add_var(t_data *l)
{
	t_params	*tmp;

	printf("her\n");
	tmp = l->list;
	while (tmp)
	{
		if (ft_in(tmp, '=') == 1)
			if (ft_verif_node(tmp, l) == 1)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}