/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:48:40 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/27 12:05:30 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print(char *str, int len)
{
	int	i;

	printf("minishell: ");
	i = 0;
	while (i < len)
		printf("%c", str[i++]);
	printf(": command not found\n");
	return (1);
}

void	ft_add_to_vars(t_params *tmp, t_data *l)
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

void	ft_verif_tmp_var(t_params *tmp, t_data *l, int i, int b)
{
	int	k;

	k = 0;
	while (tmp->str[k] != '=')
		k++;
	printf("%c\n", tmp->str[k]);
	printf("strlen: %ld, i: %d\n", ft_strlen(tmp->str), i);
	if (!(!tmp->str[k + 1] || (size_t)i != ft_strlen(tmp->str) || b > 2))
		ft_add_to_vars(tmp, l);
	ft_print(tmp->str, i);
}
