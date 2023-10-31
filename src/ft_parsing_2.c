/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:29:54 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/31 12:06:12 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_pathcmp(char *str, char *path)
{
    size_t    i;

    i = 0;
    while (str[i] == path[i])
        i++;
    if (i == ft_strlen(path) && i - ft_strlen(path) == 0)
        return (str);
    return (NULL);
}

char    **ft_search_path(char *str, t_data *l)
{
    int        i;
    char    **tmp;
    char    *line;

    i = 0;
    while (l->envp[i])
    {
        line = ft_pathcmp(l->envp[i], str);
        if (line != NULL)
            break ;
        i++;
    }
    tmp = ft_split(line, ':');
    return (tmp);
}

char    *ft_find_in_env(char *var, t_data *l)
{
    int        i;
    char    *line;

    i = 0;
    while (l->envp[i])
    {
        line = ft_pathcmp(l->envp[i], var);
        if (line != NULL)
            break ;
        i++;
    }
    return (line);
}

char    *ft_find_var(t_params *list, t_data *l)
{
    int        len;
    int        i;
    int        ct;
    char    *var;
    char    *var_in_env;

    i = 0;
    while (list->str[i] != '$')
        i++;
    ct = 1;
    while (list->str[i + ct] != ' ' && list->str[i + ct] != 34
        && (list->str[i + ct] < 7 || list->str[i + ct] > 13))
        ct++;
    var = ft_substr(list->str, i + 1, ct - 1);
    var_in_env = ft_find_in_env(var, l);
    len = ft_strlen(var) + 1;
    free(var);
    var = ft_substr(var_in_env, len, ft_strlen(var_in_env) - len);
    return (var);
}

int    ft_look_pipe(t_params **tmp, t_data *l)
{
    if (ft_strcmp((*tmp)->str, "|") == 0)
    {
        l->pos++;
        (*tmp) = (*tmp)->next;
		return (1);
    }
	return (0);
}