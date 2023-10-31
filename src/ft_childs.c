/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:03:16 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/31 17:24:03 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_childs(t_data *l)
{
	int	i;
	int	status;

	i = 0;
	while (l->child_pid[i])
		waitpid(l->child_pid[i++], &status, 0);
	if (l->pipe_nb && (dup2(l->new_fd[0], 0) == -1 ||
			close(l->new_fd[0]) || close(l->new_fd[1]) == -1))
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
}