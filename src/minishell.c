/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:13:47 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/10 12:58:02 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_access_verif(t_data *l)
{
	int		k;
	int		j;
	char	**path;
	char	*join;
	char	*command;

	path = ft_search_path(l);
	l->path = NULL;
	command = ft_strjoin("/", ft_lst_elem(l->list, 0)->str);
	j = 0;
	k = -1;
	while (path[j])
	{
		join = ft_strjoin(path[j], command);
		if (access(join, 0) == 0)
		{
			l->path = ft_strjoin(path[j], command);
			k = j;
		}
		free(join);
		free(path[j]);
		j++;
	}
	if (path)
		free(path);
	if (command)
		free(command);
	return (k);
}

int	ft_big_execute(t_data *l)
{
	if (l->pipe == 1)
		ft_pipe(l);
	else if (l->path)
	{
		l->pos = 0;
		execute_command(l);
	}
	return (0);
}

//malloc ok in this function.
int	init(t_data *l)
{
	l->params = readline("minishell-> ");
	if (!l->params)
		return (1);
	l->params_split = ft_split(l->params, ' ');
	add_history(l->params);
	ft_chained_args(l);
	if (!l->list || !l->list->str || !l->list->str[0])
		return (0);
	if (ft_lst_elem(l->list, 0))
		l->dir = opendir(ft_lst_elem(l->list, 0)->str);
	if (ft_access_verif(l) < 0 && l->list->str != NULL)
		return (printf("Command '%s' not found.\n",
			 ft_lst_elem(l->list, 0)->str));
	l->in = dup(STDIN_FILENO);
	l->out = dup(STDOUT_FILENO);
	ft_pipe_presence(l);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*l;

	(void)av;
	if (ac > 1)
	{
		perror("You cannot execute minishell with arguments.");
		exit(EXIT_FAILURE);
	}
	l = ft_calloc(sizeof(t_data), 1);
	l->envp = envp;
	l->stop_main = 1;
	printf("\033[1;32mWelcome to minishell\033[0m\n");
	while (l->stop_main)
	{
		if (init(l) != 0)
			break ;
		ft_big_execute(l);
		ft_free_all(l);
	}
	rl_clear_history();
	return (0);
}

/*
 ✔	• Afficher un prompt en l’attente d’une nouvelle commande.
 ✔	• Posséder un historique fonctionnel.
 ✔	• Chercher et lancer le bon exécutable (en se basant sur la variable d’environnement
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
