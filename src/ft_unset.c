/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:15:03 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/20 14:24:12 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

int	is_proper_env(const char *env_name)
{
	int	i;

	if (env_name == NULL || env_name[0] == '\0')
		return (0);
	i = 0;
	while (env_name[i])
	{
		if (!(ft_isalnum((unsigned char)env_name[i]) || env_name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	**ft_getenvvar(t_data *data, const char *name)
{
	int	i;
	int	j;
	int	name_len;

	if (!name || !data || !data->envp)
		return (NULL);
	i = 0;
	name_len = ft_strlen(name);
	while (data->envp[i])
	{
		j = 0;
		while (name[j] && data->envp[i][j] && name[j] == data->envp[i][j])
			++j;
		if ((data->envp[i][j] == '=' && j == name_len)
			|| !name[j])
			return (&data->envp[i]);
		++i;
	}
	return (NULL);
}

void	ft_unsetenv_2(t_data *data, char **new_envp, char **target)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->envp[i])
	{
		if (&data->envp[i] != target)
			new_envp[j++] = data->envp[i];
		else
			free(data->envp[i]);
		++i;
	}
	new_envp[j] = NULL;
	data->envp = new_envp;
}

int	ft_unsetenv(t_data *data, const char *name)
{
	char	**target;
	char	**new_envp;
	int		i;

	if (!name || !data || !data->envp)
		return (-1);
	target = ft_getenvvar(data, name);
	i = 0;
	if (!target)
		return (0);
	i = 0;
	while (data->envp[i])
		++i;
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		return (-1);
	ft_unsetenv_2(data, new_envp, target);
	return (0);
}

int	ft_unset(t_data *l)
{
	t_params	*element;
	int			error_flag;
	int			pos;
	char		*key;

	error_flag = 0;
	pos = l->pos + 1;
	element = ft_get_nth_param(l->list, pos);
	while (element)
	{
		if (!is_proper_env(element->str))
			ft_is_not_proper_env(element, &error_flag);
		else
		{
			key = element->str;
			if (ft_unsetenv(l, key) != 0)
				ft_is_not_proper_variable(key, &error_flag);
		}
		element = element->next;
	}
	ft_exit_code(&error_flag, l);
	return (l->exit_code);
}
