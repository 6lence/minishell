/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:27:17 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/09 12:52:13 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input_more(t_params *tmp, char *ct, t_data *l)
{
	char	*str;

	if (ft_strcmp(ct, "<") == 0)
		ft_open_simple_in(tmp, ct, l);
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
		while (tmp->next && !ft_operator_cmp(tmp->next))
			tmp = tmp->next;
	}
	else if (ft_strcmp(tmp->str, "<<") == 0)
		ct = "<<";
	ft_input_more(tmp, ct, l);
}

void	ft_output_more(t_params *tmp, char *ct, t_data *l)
{
	if (ft_strcmp(ct, ">") == 0)
		ft_open_simple_out(tmp, ct, l);
	else if (ft_strcmp(ct, ">>") == 0)
		ft_open_double_out(tmp, ct, l);
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
