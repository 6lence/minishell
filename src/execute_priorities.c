/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_priorities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:44:40 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/25 15:05:10 by ashalagi         ###   ########.fr       */
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
    t_params *temp = malloc(sizeof(t_params));
    temp->str = cmd_str;
    temp->operator = NONE; // Assuming NONE represents a regular command
    temp->next = NULL;
    
    char **args = malloc(MAX_ARGS * sizeof(char *));
    int i = 0, j = 0, len = strlen(cmd_str);
    char current_arg[MAX_ARG_LENGTH]; // Assuming a maximum argument length

    for (int k = 0; k < len; k++)
    {
        if (cmd_str[k] != ' ' && cmd_str[k] != '\0')
        {
            current_arg[j++] = cmd_str[k];
        }
        else
        {
            if (j > 0) // if there was a previous argument
            {
                current_arg[j] = '\0'; // null-terminate the argument
                args[i] = malloc(j + 1);
                strcpy(args[i++], current_arg); // save the argument
                j = 0; // reset for the next argument
            }
        }
    }

    if (j > 0) // for the last argument
    {
        current_arg[j] = '\0';
        args[i] = malloc(j + 1);
        strcpy(args[i++], current_arg);
    }

    args[i] = NULL; // null-terminate the arguments array

    temp->cmd = args[0]; // the command is the first argument
    temp->args = args;
    
    return temp;
}



int contains_logical_operators(t_params *tmp)
{
    t_params *current = tmp;

    printf("Starting to search for logical operators...\n"); // DEBUG: Indicating the start of the search

    while (current != NULL)
    {
        // DEBUG: Detailed information about the current node
        printf("Current Node Information:\n");
        printf("  - String: %s\n", current->str);
        printf("  - Position: %d\n", current->pos);
        printf("  - Operator: %d\n", current->operator);

        if (current->operator != NONE)
        {
            printf("Logical operator found! Operator type: %d in command: %s\n", current->operator, current->str); // DEBUG: Indicating found logical operator
            return 1;
        }
        current = current->next;
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
            if (status == 0)
            {
                // If the previous command was successful, execute the next command
                current = current->next;
                continue;
            }
            else
            {
                // If the previous command failed, skip the next command
                current = current->next->next;
            }
        }
        else if (current->operator == OR)
        {
            if (status != 0)
            {
                // If the previous command failed, execute the next command
                current = current->next;
                continue;
            }
            else
            {
                // If the previous command was successful, skip the next command
                current = current->next->next;
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