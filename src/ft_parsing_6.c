/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:27:17 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/08 17:30:59 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input_more(t_params *tmp, char *ct, t_data *l)
{
	char	*str;

	if (ft_strcmp(ct, "<") == 0)
		l->tmp_in = open(tmp->str, O_RDONLY, 0644);
	else if (ft_strcmp(ct, "<<") == 0)
	{
		tmp = tmp->next;
		printf("heredoc> ");
		str = get_next_line(0);
		while (str && ft_strcmp(str, tmp->str) != 0)
		{
			printf("heredoc> ");
			ft_putstr_fd(str, l->tmp_in);
			free(str);
			str = get_next_line(0);
		}
		if (str)
			free(str);
	}
}

void	ft_input(t_params *list, t_data *l)
{
	char		*ct;
	t_params	*tmp;

	ct = NULL;
	tmp = list;
	if (ft_strcmp(tmp->str, "<") == 0)
	{
		ct = "<";
		tmp = tmp->next;
		while (!ft_operator_cmp(tmp->next))
			tmp = tmp->next;
	}
	else if (ft_strcmp(tmp->str, "<<") == 0)
		ct = "<<";
	ft_input_more(tmp, ct, l);
}

void	ft_output_more(t_params *tmp, char *ct, t_data *l)
{
	if (ft_strcmp(ct, ">") == 0)
	{
		tmp = tmp->next;
		while (tmp)
		{
			if (ft_operator_cmp(tmp) && ft_strcmp(tmp->str, ct) != 0)
				break;
			else if (ft_operator_cmp(tmp))
			{
				if (tmp->next)
					tmp = tmp->next;
			}
			else
			{
				l->tmp_out = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (tmp->next)
					tmp = tmp->next;
				else
					break;
			}
		}
	}
	else if (ft_strcmp(ct, ">>") == 0)
		l->tmp_out = open(tmp->next->str,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
}

void	ft_output(t_params *list, t_data *l)
{
	char	*ct;

	ct = NULL;
	if (ft_strcmp(list->str, ">") == 0)
		ct = ">";
	else if (ft_strcmp(list->str, ">>") == 0)
		ct = ">>";
	ft_output_more(list, ct, l);
}

void	ft_look_in_out_put(t_params *tmp, t_data *l)
{
	t_params	*copy;

	copy = tmp;
	while (copy->next && !ft_operator_cmp(copy))
		copy = copy->next;
	if (ft_strcmp(copy->str, "<") == 0
		|| ft_strcmp(copy->str, "<< ") == 0)
		ft_input(copy, l);
	else if (ft_strcmp(copy->str, ">") == 0
		|| ft_strcmp(copy->str, ">>") == 0)
		ft_output(copy, l);
	else
	{
		l->tmp_in = l->in;
		l->tmp_out = l->out;
	}
}
