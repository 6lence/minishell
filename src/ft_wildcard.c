/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:27:29 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/06 14:42:59 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

t_params *new_node(const char *cmd, char **args)
{
    t_params *new_node = malloc(sizeof(t_params));
    new_node->cmd = ft_strdup(cmd);
    new_node->args = args;
    new_node->next = NULL;
    return new_node;
}

void delete_list(t_params *head)
{
    t_params *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->cmd);
        free(tmp);
    }
}

/*
- DIR is a datatype representing a directory stream in C. It is used to manage and
handle directories as streams, allowing you to operate on the directory's content.
- d is a pointer to a DIR type, and it holds the reference to the directory stream
opened by the opendir() function.
- When you call opendir(), it returns a pointer of type DIR that you can use to
read the directory’s contents or close the directory later.

- struct dirent is a structure type used to represent directory entries. It is used
when reading from a directory stream, providing information about the files and
subdirectories within.
- dir is a pointer to a struct dirent, and it holds the reference to directory
entries when you read them using readdir().
- The readdir() function returns a pointer to a struct dirent representing the
next directory entry in the directory stream. It returns NULL after the last
directory entry.
*/
void execute_command_with_wildcards(t_params *commands, char **envp)
{
    DIR *d;
    struct dirent *dir;
    const char **new_args;
    t_params *current;

    d = opendir(".");
    if (d == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    new_args = malloc(3 * sizeof(char *));
    if (new_args == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    current = commands;
    while (current != NULL)
    {
        pid_t pid = fork();
        if (pid == 0) // Child process
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (ft_strstr(dir->d_name, current->args[1] + 1))
                {
                    new_args[0] = current->cmd;
                    new_args[1] = dir->d_name;
                    new_args[2] = NULL;

                    execve(current->cmd, (char *const *)new_args, envp);
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
            closedir(d);
            free(new_args); // Free the allocated memory
            exit(EXIT_SUCCESS);
        }
        else if (pid < 0) // Fork failed
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else // Parent process
        {
            int status;
            waitpid(pid, &status, 0);
        }
        current = current->next;
    }
    free(new_args); // Free the allocated memory
}


int main(void)
{
    char *args[] = {"ls src", ".c", NULL};

    t_params *commands = new_node("/bin/ls", args);

    char **envp = NULL; // or get the environment variables if needed

    execute_command_with_wildcards(commands, envp);

    delete_list(commands);

    return 0;
}

/*
int main(void) // Removed argc, argv, and envp
{
    char *cmd = "/bin/ls"; // Need to specify the absolute path
    char *args[] = {"ls", "*.txt", NULL};
    char **envp = NULL; // You can set envp to NULL or get the environment variables another way if needed

    execute_command_with_wildcards(cmd, args, envp);

    return 0;
}
*/