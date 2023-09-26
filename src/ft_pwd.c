/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:35:13 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/25 15:22:12 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char *ft_pwd()
{
    char *buf = NULL;
    size_t size;

	size = 0;
    if (getcwd(NULL, 0) == NULL)
	{
        perror("getcwd");
        return NULL;
    }
    buf = (char *)malloc(size);
    if (buf == NULL)
	{
        perror("malloc");
        return NULL;
    }
    if (getcwd(buf, size) == NULL)
	{
        perror("getcwd");
        free(buf);
        return NULL;
    }
    return buf;
}