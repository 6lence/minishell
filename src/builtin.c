/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:21:48 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/13 16:01:25 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1); // command is a built-in command.
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0); //no match
}

int execute_builtin(t_data *l, t_params *tmp)
{
    int result = 0;
    char *command = tmp->str;
    char **arguments = linked_list_to_array(tmp->next);

    // Update the arguments in the t_data structure
    l->arguments = arguments;

    if (ft_strcmp(command, "echo") == 0)
        result = ft_echo(l);
    else if (ft_strcmp(command, "cd") == 0)
        result = ft_cd(l);
    else if (ft_strcmp(command, "pwd") == 0)
    {
        char* pwd = ft_pwd();
        printf("%s\n", pwd);
        free(pwd);
        result = 0; //success
    }
    else if (ft_strcmp(command, "env") == 0)
        result = ft_env(l); // If ft_env needs arguments
    else if (ft_strcmp(command, "export") == 0)
        result = ft_export(l);
    else if (ft_strcmp(command, "unset") == 0)
        result = ft_unset(l, arguments);
    
    // Free the allocated memory for arguments
    free(arguments);
    
    return (result);
}

char	**linked_list_to_array(t_params *tmp) 
{
    int count = 0;
    t_params *current = tmp;
    
    // Step 1: Count nodes in linked list
    while (current != NULL) 
    {
        count++;
        current = current->next;
    }
    // Step 2: Allocate memory for the array
    char **args = (char **)malloc(sizeof(char *) * (count + 1));
    if (args == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    // Step 3: Assign strings to the array
    current = tmp;
    for (int i = 0; i < count; i++) 
    {
        args[i] = current->str;
        current = current->next;
    }
    // Step 4: Ensure the array is NULL-terminated
    args[count] = NULL;
    return args;
}
/*
int	execute_builtin(t_data *data)
{
	int		result;

	result = 0;
	if (ft_strcmp(data->command, "echo") == 0)
		result = ft_echo(data->arguments);
	if (ft_strcmp(data->command, "cd") == 0)
		result = ft_cd(data);
	if (ft_strcmp(data->command, "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(data->command, "env") == 0)
		ft_env(data->envp);
	if (ft_strcmp(data->command, "export") == 0)
		result = ft_export(data->arguments);
	if (ft_strcmp(data->command, "unset") == 0)
		result = ft_unset(data->arguments, data->envp);
	return (result);
}
*/
/*
if (is_builtin(data->command))
{
    result = execute_builtin(&data);
}
*/
