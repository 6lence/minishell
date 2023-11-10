/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_priorities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:44:40 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/10 12:31:24 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NONE 0
#define AND 1
#define OR 2
#define ERROR -1
#define MAX_ARGS 64
#define MAX_ARG_LENGTH 256

t_params *create_temp_command_node(char *cmd_str)
{
    t_params *temp;
    temp = (t_params *)malloc(sizeof(t_params));
    temp->str = ft_strdup(cmd_str);
    temp->operator = NONE;
    temp->next = NULL;
    temp->cmd = NULL;
    temp->args = NULL;
    if (ft_strcmp(cmd_str, "&&") == 0)
        temp->operator = AND;
    else if (ft_strcmp(cmd_str, "||") == 0)
        temp->operator = OR;
    else
    {
        char **args = ft_split(cmd_str, ' ');
        int i = 0;
        if (args[i] != NULL)
        {
            temp->cmd = ft_strdup(args[i++]);
            temp->args = (char **)malloc(sizeof(char *) * MAX_ARGS);
            temp->args[0] = ft_strdup(temp->cmd);
            int j = 1;
            while (args[i] != NULL && j < MAX_ARGS - 1)
            {
                temp->args[j++] = ft_strdup(args[i++]);
            }
            temp->args[j] = NULL;
        }
        i = 0;
        while (args[i] != NULL)
        {
            free(args[i++]);
        }
        free(args);
    }
    return temp;
}

int contains_logical_operators(t_params *tmp)
{
//    t_params *current = tmp;
    while (tmp != NULL)
    {

        if (tmp->operator != NONE)
        {
            return(1);
        }
        tmp = tmp->next;
    }
    return 0;
}

int execute_operator(t_params *cmd)
{
    pid_t pid;
    int status;

    if (cmd->cmd == NULL)
    {
        fprintf(stderr, "Null command encountered.\n");
        return EXIT_FAILURE;
    }

//    printf("Executing command: %s\n", cmd->cmd); // Debugging print

    if ((pid = fork()) == -1)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0)
    {
        execvp(cmd->cmd, cmd->args);
        perror("execvp error");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            status = WEXITSTATUS(status);
        }
        else
        {
            status = EXIT_FAILURE;
        }
    }
    
//    printf("Command '%s' exited with status: %d\n", cmd->cmd, status); // Output each command's exit status
    return status;
}

int ft_execute_priorities(t_params *commands)
{
    int status = 0;
    t_params *current = commands;
    char *cmd_str = NULL;
    size_t total_length;

    while (current != NULL)
    {
//        printf("Current command/operator: %s\n", current->str); // DEBUG

        if (current->operator == NONE)
        {
            t_params *temp_cmd_node;
            if (current->next != NULL && current->next->operator == NONE)
            {
                total_length = ft_strlen(current->str) + ft_strlen(current->next->str) + 2;
                cmd_str = malloc(total_length);
                if (cmd_str == NULL)
                {
                    perror("malloc failed");
                    exit(EXIT_FAILURE);
                }
                ft_strcpy(cmd_str, current->str);
                ft_strcat(cmd_str, " ");
                ft_strcat(cmd_str, current->next->str);
                temp_cmd_node = create_temp_command_node(cmd_str);
                free(cmd_str);
            }
            else
            {
                temp_cmd_node = create_temp_command_node(current->str);
            }

            status = execute_operator(temp_cmd_node);
            free(temp_cmd_node);

            current = (current->next != NULL && current->next->operator == NONE) ? current->next->next : current->next;
        }
        else if (current->operator == AND)
        {
            if (status != 0)
            {
                // If the previous command failed, skip until the next OR or NONE operator
                while (current != NULL && current->operator == AND)
                {
                    current = current->next;
                }
            }
            else // if the previous command succeeded
            {
                current = current->next; // skip until the next logical operator
            }
        }
        else if (current->operator == OR)
        {
            if (status == 0)
            {
                while (current && current->operator != AND)
                    current = current->next;
            }
            else
                current = current->next;
        }
        else
        {
            write(2, "Unknown operator: '", 19);
            write(2, current->str, strlen(current->str));
            write(2, "'.\n", 3);
            return EXIT_FAILURE;
        }
    }
    return status;
}

void assign_operator(t_params *node)
{
    if (strcmp(node->str, "&&") == 0)
        node->operator = AND;
    else if (strcmp(node->str, "||") == 0)
        node->operator = OR;
    else if (strcmp(node->str, "&") == 0)
    {
        write(STDERR_FILENO, "error, incorrect operator '&'\n", 30);
        node->operator = ERROR;
    }
    else
        node->operator = NONE;
}