void execute_command(t_data *l, t_params *tmp)
{
    char	**args;
	pid_t	child_pid;

	t_params *current = tmp;
    
    // Assign operators to each node
    while (current != NULL)
    {
        assign_operator(current);
        current = current->next;
    }

    // Check if the command contains logical operators
    if (contains_logical_operators(tmp))
    {
        printf("Logical operators found, executing priorities.\n"); // DEBUG: Indicate entering the priorities block
		int status = ft_execute_priorities(tmp);
		printf("Finished executing priorities.\n"); // DEBUG: Indicate finished executing priorities
        if (status != 0)
        {
            char *status_str = ft_itoa(status);
            write(2, "Command execution failed with status ", 36);
            write(2, status_str, ft_strlen(status_str)); 
            write(2, "\n", 1);
            free(status_str); // Free the allocated string
        }
        return;
    }
    if (is_builtin(tmp->str))
    {
        execute_builtin(l, tmp); // Execute the built-in command directly
        return; // Return after executing the built-in command
    }
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        if (ft_access_verif(l, tmp) < 0 && tmp->str != NULL)
        {
            dup2(l->out, 1);
            printf("Command '%s' not found.\n", tmp->str);
            return;
        }
        args = ft_arguments(tmp); // Convert linked list to array of arguments
		dup2(l->tmp_in, l->in);
		dup2(l->tmp_out, l->out);
        execve(l->path, args, l->envp); // Execute the external command
    }
    wait(NULL); // Wait for the child process to finish
}