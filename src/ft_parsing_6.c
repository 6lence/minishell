/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:16:10 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/26 14:27:31 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void    ft_input_more(t_params *tmp, int ct, t_data *l)
{
    char    *str;

    if (ct == 1)
        l->tmp_in = open(tmp->str, O_RDONLY, 0644);
    else if (ct == 2)
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

void    ft_input(t_params *list, t_data *l)
{
    int            ct;
    t_params    *tmp;

    ct = 0;
    tmp = list;
    if (ft_strcmp(tmp->str, "<") == 0)
    {
        ct = 1;
        tmp = tmp->next;
        while (!ft_operator_cmp(tmp->next))
            tmp = tmp->next;
    }
    else if (ft_strcmp(tmp->str, "<<") == 0)
        ct = 2;
    ft_input_more(tmp, ct, l);
}

void	ft_output_more(t_params *tmp, int ct, t_data *l)
{
	if (ct == 1)
		l->tmp_out = open(tmp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ct == 2)
		l->tmp_out = open(tmp->next->str,
			O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
}

void    ft_output(t_params *list, t_data *l)
{
    t_params    *tmp;
    int            ct;

    tmp = list;
    ct = 0;
    if (ft_strcmp(tmp->str, ">") == 0)
        ct = 1;
    else if (ft_strcmp(tmp->str, ">>") == 0)
        ct = 2;
    tmp = tmp->next;
    ft_output_more(tmp, ct, l);
}

void    ft_look_in_out_put(t_params *tmp, t_data *l)
{
    if (ft_strcmp(tmp->str, "<") == 0
        || ft_strcmp(tmp->str, "<< ") == 0)
        ft_input(tmp, l);
    else if (ft_strcmp(tmp->str, ">")
        || ft_strcmp(tmp->str, ">>"))
        ft_output(tmp, l);
	else
	{
		l->tmp_in = l->in;
		l->tmp_out = l->out;
	}
}