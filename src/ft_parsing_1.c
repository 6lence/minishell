/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:34:37 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/06 10:26:11 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pipe_presence(t_data *l)
{
    t_params    *tmp;

    l->pipe = 0;
    tmp = l->list;
    l->pipe_nb = 0;
    while (tmp->next)
    {
        if (tmp->str[0] == '|'
            && !tmp->str[1])
        {
            l->pipe_nb++;
            l->pipe = 1;
        }
        tmp = tmp->next;
    }
}

int    ft_params_len(char **str)
{
    int    i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int    ft_chained_args(t_data *l)
{
    t_params    *new;
    int            i;

    i = 0;
    l->list = NULL;
    while (l->params_split[i])
    {
        new = malloc(sizeof(t_params));
        if (!new)
            return (1);
        new->str = l->params_split[i];
        new->pos = i;
        new->next = NULL;
        if (l->list)
        {
            new->prev = l->list;
            ft_lstlast(l->list)->next = new;
        }
        else
        {
            new->prev = NULL;
            l->list = new;
        }
        i++;
    }
    return (0);
}

void    ft_parsing(t_data *l)
{
    l->params_split = ft_calloc(ft_words(l) + 1, sizeof(char *));
    ft_fill_split(l);
    ft_chained_args(l);
    ft_look_dollar(l);
}