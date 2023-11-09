/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:15:03 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/09 21:55:05 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

int	is_proper_env(const char *env_name)
{
	int	i;

	printf("Debug: Checking env_name: %s\n", env_name);
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

	printf("Debug: Getting env var: %s\n", name);
	if (!name || !data || !data->envp)
		return (NULL);
	i = 0;
	name_len = ft_strlen(name);
	while (data->envp[i])
	{
		j = 0;
		while (name[j] && data->envp[i][j] && name[j] == data->envp[i][j])
			++j;
		if (data->envp[i][j] == '=' && j == name_len)
			return (&data->envp[i]);
		++i;
	}
	return (NULL);
}

int	ft_unsetenv(t_data *data, const char *name)
{
	char	**target;
	char	**new_envp;
	int		i;
	int		j;

	printf("Debug: Unsetting env var: %s\n", name);
	if (!name || !data || !data->envp)
		return (-1);
	target = ft_getenvvar(data, name);
	if (!target)
		return (0);
	i = 0;
	while (data->envp[i])
		++i;
	new_envp = (char **)malloc(sizeof(char *) * i);
	if (!new_envp)
		return (-1);
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		if (&data->envp[i] != target)
			new_envp[j++] = data->envp[i];
		++i;
	}
	new_envp[j] = NULL;
	if (data->envp_allocated)
	{
		free(data->envp);
		data->envp_allocated = 0;
	}
	data->envp = new_envp;
	data->envp_allocated = 1;
	return (0);
}

t_params	*ft_get_nth_param(t_params *list, int n)
{
	t_params	*current;

	current = list;
	while (current && current->pos != n)
		current = current->next;
	return (current);
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
