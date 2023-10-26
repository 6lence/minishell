/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:16:10 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/26 11:27:33 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void    ft_input_more(t_params *tmp, int ct, t_data *l)
{
    char    *str;

    if (ct == 1)
        l->tmp_file = open(tmp->str, O_RDONLY, 0644);
    else if (ct == 2)
    {
        tmp = tmp->next;
        printf("heredoc> ");
        str = get_next_line(0);
        while (str && ft_strcmp(str, tmp->str) != 0)
        {
            printf("heredoc> ");
            ft_putstr_fd(str, l->tmp_file);
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
        while (!(ft_strcmp(tmp->next->str, "<") == 0
                || ft_strcmp(tmp->next->str, "<<") == 0
                || ft_strcmp(tmp->next->str, ">") == 0
                || ft_strcmp(tmp->next->str, ">>") == 0
                || ft_strcmp(tmp->next->str, "|") == 0))
            tmp = tmp->next;
    }
    else if (ft_stcmp(tmp->str, "<<") == 0)
        ct = 2;
    else
    {
        l->tmp_file = l->in;
        return ;
    }
    ft_input_more(tmp, ct, l);
}

void    ft_output(t_params *list, t_data *l)
{
    t_params    *tmp;
    int            ct;

    tmp = list;
    ct = 0;
    if (ft_strcmp(tmp->str, ">") == 0)
    {
        ct = 1;
        tmp = tmp->next;
    }
    else if (ft_strcmp(tmp->str, ">>") == 0)
    {
        
    }
}

void    ft_look_in_out_put(t_params *tmp, t_data *l)
{
    if (ft_strcmp(tmp->str, "<") == 0
        || ft_strmp(tmp->str, "<< ") == 0)
        ft_input(tmp, l);
    else if (ft_strcmp(tmp->str, ">")
        || ft_strcmp(tmp->str, ">>"))
        ft_output(tmp, l);
}