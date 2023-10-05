/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:34:37 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/05 13:49:10 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_presence(t_data *l)
{
	t_params	*tmp;

	l->pipe = 0;
	tmp = l->list;
	while (tmp->next)
	{
		if (tmp->str[0] == '|')
			l->pipe = 1;
		tmp = tmp->next;
	}
}

int	ft_params_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_chained_args(t_data *l)
{
	t_params	*new;
	int			i;
	int			params;

	i = 0;
	l->list = NULL;
	params = ft_params_len(l->params_split);
	while (i < params)
	{
		new = malloc(sizeof(t_params));
		if (!new)
			return (1);
		new->str = l->params_split[i];
		new->pos = i;
		new->next = NULL;
		if (l->list)
		{
			new->prev = l->list;
			ft_lstlast(l->list)->next = new;
		}
		else
		{
			new->prev = NULL;
			l->list = new;
		}
		i++;
	}
	return (0);
}

// Function to parse user input and return command and arguments
void	get_command_arguments(const char *input,
			char *command, char **arguments)
{
	char	**tokens;

	tokens = ft_split(input, ' ');
	if (!tokens || !tokens[0])
	{
		command = NULL;
		*arguments = NULL;
		return ;
	}
	command = ft_strjoin(command, tokens[0]);
	*arguments = tokens[1];
}
