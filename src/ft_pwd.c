/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:35:13 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/09 15:09:34 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(void)
{
	char	*buf;
	size_t	size;

	size = 1024;
	buf = (char *)malloc(size);
	if (buf == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	if (getcwd(buf, size) == NULL)
	{
		perror("getcwd");
		free(buf);
		return (NULL);
	}
	return (buf);
}

/*
//need to free the buffer when done
//if system support, possible simplify the function by directly using getcwd(NULL, 0)
char *ft_pwd()
{
    char *buf = getcwd(NULL, 0);
    if (buf == NULL)
    {
        perror("getcwd");
    }
    return buf;
}

*/

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
