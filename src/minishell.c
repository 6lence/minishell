/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:13:47 by ashalagi          #+#    #+#             */
/*   Updated: 2023/09/20 09:21:06 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>

// Function to read a line of text from the terminal
char *readline()
{
    char *line = NULL;
    size_t len = 0;
    size_t index = 0;
    char c;

    //printf("Enter parameters: ");
    //STDIN_FILENO used to read a single character from the standard input (stdin) into the variable c.
	//It reads one character at a time from the keyboard input
    write(STDOUT_FILENO, "\033[1;32mWelcome to minishell\033[0m\n", 32);
	while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n')
    {
        if (index == len)
        {
            len += 64; // Increase the buffer size as needed
            char *new_line = ft_realloc(line, len);
            if (new_line == NULL)
            {
                //print an error message if a memory allocation error occurs
				//during the dynamic memory allocation process with malloc or realloc
				perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            line = new_line;
        }
        line[index++] = c;
    }
    if (index == 0)
    {
        // Handle EOF(end of file) without any input
        return NULL;
    }
    // Null-terminate the line
    if (index == len)
    {
        len++;
        char *new_line = ft_realloc(line, len);
        if (new_line == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        line = new_line;
    }
    line[index] = '\0';

    return line;
}

// Function to display the given parameters
void show_parameters(const char *parameters)
{
    char **tokens;
    int i; // Declare and initialize loop counter

	i = 0;
    // Represents a single parameter obtained from the input string,
    // which may contain multiple parameters separated by spaces.
    tokens = ft_split(parameters, ' ');
    if (tokens)
    {
        // Use a while loop to iterate through tokens and print parameters
        while (tokens[i] != NULL)
        {
            printf("Parameter: %s\n", tokens[i]);
            i++; // Increment the loop counter
        }
        i = 0; // Reset the loop counter for freeing memory
        // Use another while loop to free the memory allocated for tokens
        while (tokens[i] != NULL)
        {
            free(tokens[i]);
            i++; // Increment the loop counter
        }

        free(tokens);
    }
}

int main(int ac, char **av)
{
    int i;
	int j;

    if (ac > 1)
    {
        i = 1;
        while (i < ac)
        {
            show_parameters(av[i]);
            i++;
        }
    }
    else
    {
        char *parameters = readline();
        
        // Parse user input to get the command and arguments
        char *command;
        char **arguments;
        parse_input(parameters, &command, &arguments);
        
        // Check if a command was provided
        if (command)
		{
            printf("Command: %s\n", command);

            // Print the arguments
            if (arguments)
			{
                printf("Arguments:\n");
                j = 0;
                while (arguments[j] != NULL)
				{
                    printf("  %s\n", arguments[j]);
                    j++;
                }
            }
			// Execute the command with its arguments
            execute_command(command, arguments);
        }
        free(parameters);
    }
    return EXIT_SUCCESS;
}


/*
./minishell /bin/ls -l
./minishell /bin/echo Hello, world!
./minishell /bin/nonexistentcommand

*/




/*
int main(int argc, char **argv)
{
    // Check if the user provided a command
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command> [arguments...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Construct the argument list for execve
    char **args = argv + 1; // Skip the program name

    // Create a child process
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        // This code runs in the child process
        // Execute the command
        if (execve(args[0], args, NULL) == -1)
        {
            // If execve returns, an error occurred
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // This code runs in the parent process
        // Wait for the child process to complete
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return EXIT_SUCCESS;
}
*/

/*
• Afficher un prompt en l’attente d’une nouvelle commande.
• Posséder un historique fonctionnel.
• Chercher et lancer le bon exécutable (en se basant sur la variable d’environnement
  PATH, ou sur un chemin relatif ou absolu).
• Ne pas utiliser plus d’une variable globale. Réfléchissez-y car vous devrez justifier
  son utilisation.
• Ne pas interpréter de quotes (guillemets) non fermés ou de caractères spéciaux non
  demandés dans le sujet, tels que \ (le backslash) ou ; (le point-virgule).
• Gérer ’ (single quote) qui doit empêcher le shell d’interpréter les méta-caractères
  présents dans la séquence entre guillemets.
• Gérer " (double quote) qui doit empêcher le shell d’interpréter les méta-caractères
  présents dans la séquence entre guillemets sauf le $ (signe dollar).
• Implémenter les redirections :
    < doit rediriger l’entrée.
    > doit rediriger la sortie.
    << doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne
    contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
    >> doit rediriger la sortie en mode append.
• Implémenter les pipes (caractère |). La sortie de chaque commande de la pipeline
  est connectée à l’entrée de la commande suivante grâce à un pipe.
• Gérer les variables d’environnement (un $ suivi d’une séquence de caractères)
  qui doivent être substituées par leur contenu.
• Gérer $? qui doit être substitué par le statut de sortie de la dernière pipeline
  exécutée au premier plan.
• Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent fonctionner comme dans bash.
• En mode interactif :
    - ctrl-C affiche un nouveau prompt sur une nouvelle ligne. ◦ ctrl-D quitte le shell.
    - ctrl-\ ne fait rien.
• Votre shell doit implémenter les builtins suivantes :
    - echo et l’option -n
    -cd uniquement avec un chemin relatif ou absolu ◦ pwd sans aucune option
    - export sans aucune option
    - unset sans aucune option
    - env sans aucune option ni argument
    - exit sans aucune option

*/

