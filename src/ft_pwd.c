/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:35:13 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/28 07:58:50 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char *ft_pwd()
{
    char *buf = NULL;
    size_t size;

	size = 64;
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

/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *currentDirectory = ft_pwd();

    if (currentDirectory != NULL)
    {
        printf("Current Directory: %s\n", currentDirectory);
        free(currentDirectory);
    }
    else
    {
        printf("Failed to retrieve current directory.\n");
    }

    return 0;
}
*/