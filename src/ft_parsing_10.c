/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_10.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:07:30 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 21:47:08 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input_more(t_params *tmp, t_data *l)
{
	char	*str;

	tmp = tmp->next;
	ft_putstr_fd("heredoc> ", l->out);
	str = get_next_line(0);
	if (pipe(l->new_fd) < 0)
		return (perror("error: fatal\n"));
	while (str && ft_strcmp(ft_substr(str, 0, ft_strlen(str) - 1), tmp->str))
	{
		ft_putstr_fd("heredoc> ", l->out);
		ft_putstr_fd(str, l->new_fd[1]);
		free(str);
		str = get_next_line(0);
	}
	if (str)
		free(str);
	l->tmp_in = l->new_fd[0];
	close(l->new_fd[1]);
}

void	ft_input(t_params *tmp, t_data *l, char *ct)
{
	if (!tmp->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_operator_cmp(tmp) && ft_strcmp(tmp->str, ct))
			break ;
		if (!ft_operator_cmp(tmp))
			l->tmp_in = open(tmp->str, O_RDONLY, 0644);
		if (l->tmp_in < 0)
		{
			printf("minishell: %s: No such file or directory\n", tmp->str);
			break ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
}

void	ft_look_in(t_params *tmp, t_data *l)
{
	t_params	*copy;
	char		*ct;

	copy = tmp;
	ct = NULL;
	while (copy->next)
	{
		if (!ft_strcmp(copy->str, "<") || !ft_strcmp(copy->str, "<<"))
		{
			ct = copy->str;
			break ;
		}
		copy = copy->next;
	}
	if (ct && !ft_strcmp(ct, "<"))
		ft_input(copy, l, ct);
	if (ct && !ft_strcmp(ct, "<<"))
		ft_input_more(copy, l);
}
