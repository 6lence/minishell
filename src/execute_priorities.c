/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_priorities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:44:40 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/08 12:39:19 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NONE 0
#define AND 1
#define OR 2
#define PAREN 3
#define ERROR -1
#define OPEN_PAREN '('
#define CLOSE_PAREN ')'
#define MAX_ARGS 64
#define MAX_ARG_LENGTH 256

t_params *create_temp_command_node(char *cmd_str, int is_within_parens)
{
    t_params *temp;
    temp = (t_params *)malloc(sizeof(t_params));
    temp->str = ft_strdup(cmd_str);
    temp->operator = NONE;
    temp->next = NULL;
    temp->cmd = NULL;
    temp->args = NULL;

    printf("Creating node for: %s\n", cmd_str); // DEBUG

    if (ft_strcmp(cmd_str, "&&") == 0)
        temp->operator = AND;
    else if (ft_strcmp(cmd_str, "||") == 0)
        temp->operator = OR;
    else if (ft_strcmp(cmd_str, "(") == 0)
        temp->operator = OPEN_PAREN;
    else if (ft_strcmp(cmd_str, ")") == 0)
        temp->operator = CLOSE_PAREN;
    else if (is_within_parens)
        temp->operator = PAREN;
    else // treat as command with arguments
    {
        char **args = ft_split(cmd_str, ' ');
        int i = 0;

        if (args[i] != NULL) // Check if there is at least a command
        {
            printf("DEBUG: Setting CMD: %s\n", args[i]);
            temp->cmd = ft_strdup(args[i++]);
            printf("DEBUG: CMD set in node: %s\n", temp->cmd);

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

    printf("Starting to search for logical operators and parentheses...\n"); // DEBUG: Indicating the start of the search

    while (tmp != NULL)
    {
        // DEBUG: Detailed information about the current node
        printf("Current Node Information:\n");
        printf("  - String: %s\n", tmp->str);
        printf("  - Position: %d\n", tmp->pos);
        printf("  - Operator: %d\n", tmp->operator);

        if (tmp->operator != NONE)
        {
            printf("Logical operator found! Operator type: %d in command: %s\n", tmp->operator, tmp->str); // DEBUG: Indicating found logical operator
            return 1;
        }
        if (ft_strchr(tmp->str, '(') || ft_strchr(tmp->str, ')'))
        {
            printf("Parentheses found in command: %s\n", tmp->str);
            return PAREN;
        }
        tmp = tmp->next;
    }

    printf("No logical operators found in the provided commands.\n"); // DEBUG: Indicating no logical operators were found
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

    printf("Executing command: %s\n", cmd->cmd); // Debugging print

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
    
    printf("Command '%s' exited with status: %d\n", cmd->cmd, status); // Output each command's exit status
    return status;
}

int ft_execute_priorities(t_params *commands)
{
    int status = 0;
    t_params *current = commands;
    char *cmd_str = NULL;

    while (current != NULL)
    {
        printf("Current command/operator: %s\n", current->str); // DEBUG

        if (current->operator == NONE)
        { // If it's a command
            t_params *temp_cmd_node;
            if (current->next != NULL && current->next->operator == NONE)
            { // Check if the next node is also a command part
                cmd_str = malloc(strlen(current->str) + strlen(current->next->str) + 2);
                sprintf(cmd_str, "%s %s", current->str, current->next->str);
                temp_cmd_node = create_temp_command_node(cmd_str, 0);
                free(cmd_str); // free the combined command string after creating the node
            }
            else
            {
                temp_cmd_node = create_temp_command_node(current->str, 0);
            }

            status = execute_operator(temp_cmd_node);
            free(temp_cmd_node); // Free the temporary node

            // Move to the next node after the command or combined command
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
            printf("Unknown operator/command: %s\n", current->str); // DEBUG: Indicate unrecognized operator/command
            write(2, "Unknown operator: '", 19);
            write(2, current->str, strlen(current->str));
            write(2, "'.\n", 3);
            return EXIT_FAILURE; // Or handle error differently
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
    printf("Node: %s, Operator: %d\n", node->str, node->operator);
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

/*
int ft_execute_priorities(t_params *commands)
{
    int status = 0;
    int paren_count = 0;
    t_params *current = commands;
    char *cmd_str = NULL;

    while (current != NULL)
    {
        printf("Current command/operator: %s\n", current->str); // DEBUG

        if (current->operator == NONE)// || current->operator == PAREN)
        { // If it's a command
            t_params *temp_cmd_node;
            if (current->next != NULL && current->next->operator == NONE)
            { // Check if the next node is also a command part
                char *cmd_str = malloc(strlen(current->str) + strlen(current->next->str) + 2);
                sprintf(cmd_str, "%s %s", current->str, current->next->str);
                temp_cmd_node = create_temp_command_node(cmd_str, 0);
            }
            else
            {
                temp_cmd_node = create_temp_command_node(current->str, 0);
            }

            status = execute_operator(temp_cmd_node);
            
            if (current->next != NULL && current->next->operator == NONE)
            {
                free(cmd_str); // free the combined command string
                current = current->next->next; // Move to the next node after the combined command
            }
            else
            {
                current = current->next;
            }

            free(temp_cmd_node); // Free the temporary node
        }
        else if (current->operator == OPEN_PAREN)
        {
            t_params *sub_cmds = NULL; // hold subcommands inside parentheses
            t_params *sub_cmd_last = NULL;

            paren_count = 1;
            current = current->next;

            printf("Parentheses found, processing enclosed commands.\n");
            while (current && paren_count > 0)
            {
                if (current->operator == OPEN_PAREN)
                {
                    current = current->next;
                    status = ft_execute_priorities(current); // Pass a pointer to the current node
                    if (status != EXIT_SUCCESS)
                    {
                        return status;
                    }
                    continue; // Skip the rest of the loop and proceed with the next command
                }
                else if (current->operator == CLOSE_PAREN)
                {
                    // Return to the caller function, effectively ending the recursion and going back one level
                    return status;
                }
                if (paren_count > 0)
                {
                    // Add command to subcommand list if we are not at the closing parenthesis
                    t_params *new_sub_cmd = create_temp_command_node(current->str, 1);
                    if (!new_sub_cmd)
                    {
                        // Handle memory allocation failure
                        perror("Failed to allocate memory for subcommand node");
                        // Consider freeing any allocated resources here before returning
                        free_subcommands(sub_cmds);
                        return (EXIT_FAILURE);
                    }
                    if (sub_cmds == NULL)
                    {
                        sub_cmds = new_sub_cmd;
                    }
                    else
                    {
                        sub_cmd_last->next = new_sub_cmd;
                    }
                    sub_cmd_last = new_sub_cmd;
                }
                 current = current->next; // Move to the next command/operator
            }
            if (paren_count != 0)
            {
                write (2, "Mismatched parentheses.\n", 24);
                free_subcommands(sub_cmds);
                return (EXIT_FAILURE);
            }

            // Execute the collected subcommands
            status = ft_execute_priorities(sub_cmds);
            free_subcommands(sub_cmds);
            if (status != EXIT_SUCCESS)
            {
                write(2, "Subcommand execution failed.\n", 29);
                free_subcommands(sub_cmds);
                return (status);
            }

            free_subcommands(sub_cmds);
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
                while (current && (!ft_operator_cmp(current) && current->operator != AND))
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
        else if (current->operator == CLOSE_PAREN)
        {
            write(2, "Error: Unmatched closing parenthesis.\n", 38);
            return EXIT_FAILURE;
        }
        else
        {
            printf("Unknown operator/command: %s\n", current->str); // DEBUG: Indicate unrecognized operator/command
            write(2, "Unknown operator: '", 19);
            write(2, current->str, strlen(current->str));
            write(2, "'.\n", 3);
            return EXIT_FAILURE; // Or handle error differently
        }
    }
    if (paren_count > 0)
    {
        write(2, "Error: Unmatched closing parenthesis.\n", 38);
        return EXIT_FAILURE;
    }
    return status;
}
*/