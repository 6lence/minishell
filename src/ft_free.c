/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:13:35 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/05 17:22:02 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_params *l)
{
	t_params	*tmp;

	if (l)
	{
		while (l)
		{
			tmp = l;
			l = l->next;
			tmp->next = NULL;
			free(tmp);
		}
	}
}

void	ft_free_all_more(t_data *l)
{
	if (l->new_fd[0])
		close(l->new_fd[0]);
	if (l->new_fd[1])
		close(l->new_fd[1]);
	if (l->old_fd[0])
		close(l->old_fd[0]);
	if (l->old_fd[1])
		close(l->old_fd[1]);
	if (l)
		ft_free_list(l->list);
}

void	ft_free_all(t_data *l)
{
	int	i;

	if (l->path)
		free(l->path);
	if (l->params)
		free(l->params);
	i = 0;
	while (l->params_split[i])
		free(l->params_split[i++]);
	if (l->params_split)
		free(l->params_split);
	if (l->command)
		free(l->command);
	i = 0;
	while (l->arguments[i])
		free(l->arguments[i++]);
	if (l->arguments[i])
		free(l->arguments);
	ft_free_all_more(l);
}