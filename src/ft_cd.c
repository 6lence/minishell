/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:00:56 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/13 15:43:18 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_variable(char **envp, const char *var_name)
{
	int	index;

	index = 0;
	while (envp[index] != NULL)
	{
		if (ft_strncmp(envp[index], var_name, \
				ft_strlen(var_name)) == 0 \
					&& envp[index][ft_strlen(var_name)] == '=')
		{
			return (index);
		}
		index++;
	}
	return (-1);
}

void	add_env_variable(char ***envp, char *argument)
{
	int		envp_len;
	char	**new_envp;

	envp_len = 0;
	while ((*envp)[envp_len] != NULL)
	{
		envp_len++;
	}
	new_envp = (char **)ft_realloc(*envp, (envp_len + 2) * sizeof(char *));
	if (!new_envp)
	{
		ft_putstr_fd("Memory allocation error\n", 2);
		exit(1);
	}
	new_envp[envp_len] = ft_strdup(argument);
	new_envp[envp_len + 1] = NULL;
	*envp = new_envp;
}

void	handle_env_variable(char ***envp, const char *var_name, char *argument)
{
	int	index;

	index = find_env_variable(*envp, var_name);
	if (index != -1)
		(*envp)[index] = ft_strdup(argument);
	else
		add_env_variable(envp, argument);
}

int	ft_cd_2(t_data *l, const char *new_dir)
{
	char	cwd[1024];
	char	*new_pwd;

	if (new_dir == NULL)
		return (-1);
	if (chdir(new_dir) == -1)
	{
		perror("cd");
		return (-1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return (-1);
	}
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
	{
		perror("malloc");
		return (-1);
	}
	handle_env_variable(&(l->envp), "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

int	ft_cd(t_data *l)
{
	char		*new_dir;
	char		cwd[1024];
	char		*old_pwd;
	t_params	*element;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return (-1);
	}
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (!old_pwd)
	{
		perror("malloc");
		return (-1);
	}
	handle_env_variable(&(l->envp), "OLDPWD", old_pwd);
	free(old_pwd);
	element = ft_list_elem(l->list, l->pos + 1);
	if (element)
		new_dir = element->str;
	else
		new_dir = NULL;
	return (ft_cd_2(l, new_dir));
}
