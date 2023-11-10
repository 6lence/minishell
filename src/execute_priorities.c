/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_priorities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:44:40 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/10 09:43:44 by ashalagi         ###   ########.fr       */
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

//    printf("Creating node for: %s\n", cmd_str); // DEBUG

    if (ft_strcmp(cmd_str, "&&") == 0)
        temp->operator = AND;
    else if (ft_strcmp(cmd_str, "||") == 0)
        temp->operator = OR;
    else // treat as command with arguments
    {
        char **args = ft_split(cmd_str, ' ');
        int i = 0;

        if (args[i] != NULL) // Check if there is at least a command
        {
//            printf("DEBUG: Setting CMD: %s\n", args[i]);
            temp->cmd = ft_strdup(args[i++]);
//            printf("DEBUG: CMD set in node: %s\n", temp->cmd);

            // Allocate and initialize arguments including the cmd as the first argument
            temp->args = (char **)malloc(sizeof(char *) * MAX_ARGS);
            temp->args[0] = ft_strdup(temp->cmd);

            // Copy the rest of the arguments
            int j = 1;
            while (args[i] != NULL && j < MAX_ARGS - 1)
            {
                temp->args[j++] = ft_strdup(args[i++]);
            }
            temp->args[j] = NULL; // Null terminate the args array
        }

        // Free the memory allocated by ft_split
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

//    printf("Starting to search for logical operators and parentheses...\n"); // DEBUG: Indicating the start of the search

    while (tmp != NULL)
    {
        // // DEBUG: Detailed information about the current node
        // printf("Current Node Information:\n");
        // printf("  - String: %s\n", tmp->str);
        // printf("  - Position: %d\n", tmp->pos);
        // printf("  - Operator: %d\n", tmp->operator);

        if (tmp->operator != NONE)
        {
//            printf("Logical operator found! Operator type: %d in command: %s\n", tmp->operator, tmp->str); // DEBUG: Indicating found logical operator
            return 1;
        }
        tmp = tmp->next;
    }

//    printf("No logical operators found in the provided commands.\n"); // DEBUG: Indicating no logical operators were found
    return 0;
}

// same fuction as in ft_logial_and
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
                // If the previous command was successful, skip until the next AND or NONE operator
                while (current && current->operator != AND)
                {
                    current = current->next;
                }
            }
            else
            {
                // If the previous command failed, proceed to the next command
                current = current->next;
            }
        }
        else
        {
//            printf("Unknown operator/command: %s\n", current->str); // DEBUG: Indicate unrecognized operator/command
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
    else if (strcmp(node->str, "|") == 0)
    {
        write(STDERR_FILENO, "error, incorrect operator '|'\n", 30);
        node->operator = ERROR;
    }
    else
    {
        node->operator = NONE;
    }
    
    // DEBUG: Check operator assignment
//    printf("Node: %s, Operator: %d\n", node->str, node->operator);
}

void free_subcommand_args(char **args)
{
    if (args != NULL)
    {
        int i = 0;
        while (args[i] != NULL)
        {
            free(args[i]); // Free each argument string
            i++;
        }
        free(args); // Finally, free the array itself
    }
}

void free_subcommands(t_params *sub_cmds)
{
    while (sub_cmds != NULL)
    {
        t_params *tmp = sub_cmds;
        sub_cmds = sub_cmds->next; // Move to next command before freeing current

        // Free the dynamically allocated members
        if (tmp->str != NULL)
        {
            free(tmp->str);
        }
        if (tmp->cmd != NULL)
        {
            free(tmp->cmd);
        }
        
        // Free the arguments array
        free_subcommand_args(tmp->args);

        // Finally free the t_params structure itself
        free(tmp);
    }
}