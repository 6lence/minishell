/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:42:50 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/17 16:47:11 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_or_update_env_2(t_data *data, char *new_env_entry)
{
	int		j;
	char	**new_envp;

	j = 0;
	new_envp = (char **)malloc(sizeof(char *) * (array_length(data->envp) + 2));
	if (!new_envp)
	{
		free(new_env_entry);
		return (-1);
	}
	while (data->envp[j])
	{
		new_envp[j] = data->envp[j];
		j++;
	}
	new_envp[j] = new_env_entry;
	new_envp[j + 1] = NULL;
	data->envp = new_envp;
	return (0);
}

int	add_or_update_env(t_data *data, char *key, char *value)
{
	int		i;
	char	*new_env_entry;
	char	*tmp;

	i = 0;
	if (ft_in_equal(key, '='))
		new_env_entry = ft_strjoin(key, "=");
	else
		new_env_entry = ft_strdup(key);
	if (value)
	{
		tmp = new_env_entry;
		new_env_entry = ft_strjoin(new_env_entry, value);
		free(tmp);
	}
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, ft_strlen(key)) == 0 \
				&& data->envp[i][ft_strlen(key)] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = new_env_entry;
			return (0);
		}
		i++;
	}
	return (add_or_update_env_2(data, new_env_entry));
}

int	ft_export(t_data *l)
{
	t_params	*element;
	int			pos;

	pos = l->pos + 1;
	if (pos >= ft_lstsize(l->list))
	{
		ft_print_env(l->envp);
		return (0);
	}
	element = ft_list_elem(l->list, pos);
	if (!element)
	{
		ft_print_env(l->envp);
		return (0);
	}
	if (!valid_env_name(element->str))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(element->str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (-1);
	}
	return (ft_export_parse_key_value(l, element));
}

int	ft_export_parse_key_value(t_data *l, t_params *element)
{
	char		*equal_sign;
	char		*key;
	char		*value;

	equal_sign = ft_strchr(element->str, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		key = element->str;
		value = equal_sign + 1;
	}
	else
	{
		key = element->str;
		value = NULL;
	}
	return (ft_export_final(l, key, value));
}

int	ft_export_final(t_data *l, char *key, char *value)
{
	int	status;

	if (!valid_env_name(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		if (key != NULL)
			ft_putstr_fd(key, 2);
		else
			ft_putstr_fd("", 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (-1);
	}
	status = add_or_update_env(l, key, value);
	if (status != 0)
		printf ("Error status");
	return (0);
}

/*
int	ft_export(t_data *l)
{
	t_params	*element;
	char		*key;
	char		*value;
	char		*equal_sign;
	int			pos;

	pos = l->pos + 1;
	if (pos >= ft_lstsize(l->list))
	{
		ft_print_env(l->envp);
		return (0);
	}
	element = ft_list_elem(l->list, pos);
	if (!element)
	{
		ft_print_env(l->envp);
		return (0);
	}
	if (!valid_env_name(element->str))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(element->str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (-1);
	}
	equal_sign = ft_strchr(element->str, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		key = element->str;
		value = equal_sign + 1;
	}
	else
	{
		key = element->str;
		value = NULL;
	}
	if (!valid_env_name(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		if (key != NULL)
			ft_putstr_fd(key, 2);
		else
		{
			ft_putstr_fd("", 2);
		}
		ft_putendl_fd("': not a valid identifier", 2);
		return (-1);
	}
	int	status = add_or_update_env(l, key, value);
	if (status != 0)
	{
		printf ("Error status");
	}
	return (0);
}
*/

/*
static void free_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
*/
