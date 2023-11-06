/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_priorities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:44:40 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/06 14:27:45 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NONE 0
#define AND 1
#define OR 2
#define PAREN 3
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

    printf("Creating node for: %s\n", cmd_str); // DEBUG

    // Check for logical operators
    if (ft_strcmp(cmd_str, "&&") == 0)
    {
        temp->operator = AND;
    }
    else if (ft_strcmp(cmd_str, "||") == 0)
    {
        temp->operator = OR;
    }
    else if ((ft_strcmp(cmd_str, "(") == 0)&& (ft_strcmp(cmd_str, ")") == 0))
    {
        temp->operator = PAREN;
    }
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

    printf("Starting to search for logical operators...\n"); // DEBUG: Indicating the start of the search

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


// with () and && and ||
#include <stdio.h> // Include this for printf

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
                char *cmd_str = malloc(strlen(current->str) + strlen(current->next->str) + 2);
                sprintf(cmd_str, "%s %s", current->str, current->next->str);
                temp_cmd_node = create_temp_command_node(cmd_str);
            }
            else
            {
                temp_cmd_node = create_temp_command_node(current->str);
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
        else if (current->operator == PAREN)
        {
            printf("Parentheses found, skipping enclosed commands.\n"); // DEBUG: Indicate parentheses found
            
            // Skip the commands inside the parentheses. 
            // You might want to enhance this logic based on how you’ve structured commands inside parentheses.
            while (current != NULL && current->operator != PAREN)
            {
                current = current->next;
            }
            if (current != NULL) // Skip the closing parenthesis
                current = current->next;
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
    {
        node->operator = AND;
    }
    else if (strcmp(node->str, "||") == 0)
    {
        node->operator = OR;
    }
    else
    {
        node->operator = NONE;
    }
    
    // DEBUG: Check operator assignment
    printf("Node: %s, Operator: %d\n", node->str, node->operator);
}

/*
Call this function wherever you create or update nodes.
For instance, if you have a function to insert a new command into your
linked list, you should call assign_operator() within that function.
*/




/*

#include "minishell.h"
#include <stdio.h>

int main()
{
    // Test 1: Command without logical operators or parentheses
    t_params cmd1 = {NULL, "echo Hello", 0, NULL, "echo", (char *[]){"echo", "Hello", NULL}, NONE};
    assign_operator(&cmd1);
    printf("Test 1 status: %d\n", ft_execute_priorities(&cmd1));

    // Test 2: Command sequence with AND operator
    t_params cmd2b = {NULL, "false", 0, NULL, "false", (char *[]){"false", NULL}, NONE};
    assign_operator(&cmd1);
    t_params cmd2a = {NULL, "echo Hello", 0, &cmd2b, "echo", (char *[]){"echo", "Hello", NULL}, AND};
    assign_operator(&cmd1);
    printf("Test 2 status: %d\n", ft_execute_priorities(&cmd2a));

    // Test 3: Command sequence with OR operator
    t_params cmd3b = {NULL, "echo World", 0, NULL, "echo", (char *[]){"echo", "World", NULL}, NONE};
    assign_operator(&cmd1);
    t_params cmd3a = {NULL, "false", 0, &cmd3b, "false", (char *[]){"false", NULL}, OR};
    assign_operator(&cmd1);
    printf("Test 3 status: %d\n", ft_execute_priorities(&cmd3a));

    // Test 4: Command sequence with parentheses (This test assumes that parentheses are already handled in your linked list)
    // This example assumes that parentheses commands are linked as next nodes and the PAREN operator node is used to skip them if necessary.
    t_params cmd4c = {NULL, "echo InParen", 0, NULL, "echo", (char *[]){"echo", "InParen", NULL}, NONE};
    assign_operator(&cmd1);
    t_params cmd4b = {NULL, "", PAREN, &cmd4c, "", NULL, PAREN};
    assign_operator(&cmd1);
    t_params cmd4a = {NULL, "echo BeforeParen", 0, &cmd4b, "echo", (char *[]){"echo", "BeforeParen", NULL}, NONE};
    assign_operator(&cmd1);
    printf("Test 4 status: %d\n", ft_execute_priorities(&cmd4a));

    return 0;
}
*/
/*
Moving forward, you might want to:

Enhance Parentheses Handling: If you want the parentheses to influence the execution
flow more (for instance, by implementing subshells or grouped command execution),
you might want to adjust the logic inside the parentheses handling part.

Error Handling: Consider enhancing error handling, for example, mismatched parentheses,
unknown operators, or commands that could not be found/executed.

Code Modularity: Your functions are well separated by functionality. You might want
to keep this modularity as your code grows, maybe even moving some functions to
separate files based on their roles.

Testing: You might want to continue thorough testing with more complex command sequences,
nested parentheses, and various combinations of logical operators to ensure that all
cases are correctly handled.

Remove Debug Prints: Once you are satisfied with the functionality, you might want
to remove or toggle off debug prints to clean up the output.
*/
/*
Test 1

Command: echo Hello
Command Exit Status: 0 (successful execution)
Test Status: 0

Test 2

Command: echo Hello
Command Exit Status: 0 (successful execution)
Command: false
Command Exit Status: 1 (unsuccessful execution)
Test Status: 1 (because the second command failed)

Test 3

Command: false
Command Exit Status: 1 (unsuccessful execution)
Command: echo World
Command Exit Status: 0 (successful execution)
Test Status: 0 (because of the OR operator; even though the first command failed, the second command was executed)

Test 4

Command: echo BeforeParen
Command Exit Status: 0 (successful execution)
Command: echo InParen
Command Exit Status: 0 (successful execution)
Test Status: 0 (both commands executed successfully)
*/