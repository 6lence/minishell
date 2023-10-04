/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:42:50 by ashalagi          #+#    #+#             */
/*   Updated: 2023/10/04 09:47:31 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
}

static int	valid_env_name(char *arg)
{
	int		i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	add_or_update_env(t_data *data, char *arg)
{
	int		i;
	char	*new_env;
	char	**new_envp;

	i = -1;
	while (data->envp[++i])
		if (ft_strncmp(data->envp[i], arg, ft_strlen(arg)) == 0 &&
			data->envp[i][ft_strlen(arg)] == '=')
			return ;
	new_env = ft_strjoin(arg, "=");
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (data->envp[++i])
		new_envp[i] = ft_strdup(data->envp[i]);
	new_envp[i] = new_env;
	new_envp[i + 1] = NULL;
	free(data->envp); // Free old envp here, you might need to free its elements too
	data->envp = new_envp;
}

void	ft_export(t_data *data)
{
	if (!(data->arguments[1])) // If no argument after ft_export
	{
		print_envp(data->envp);
		return ;
	}
	if (!valid_env_name(data->arguments[1]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(data->arguments[1], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	add_or_update_env(data, data->arguments[1]);
}

#include "minishell.h"

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

int main(void)
{
    t_data data;

    // Initialization of data
    data.envp = (char **)malloc(sizeof(char *) * 4); // Example environment
    if (!data.envp)
        return (1); // Handle memory allocation failure
    data.envp[0] = ft_strdup("USER=root");
    data.envp[1] = ft_strdup("HOME=/root");
    data.envp[2] = ft_strdup("SHELL=/bin/bash");
    data.envp[3] = NULL;

    // No arguments: should print the environment
    data.arguments = (char **)malloc(sizeof(char *) * 2);
    if (!data.arguments)
    {
        free_envp(data.envp);
        return (1); // Handle memory allocation failure
    }
    data.arguments[0] = ft_strdup("ft_export");
    data.arguments[1] = NULL;
    ft_export(&data);
    free(data.arguments[0]);
    free(data.arguments);

    // With valid argument: should add or update environment variable
    data.arguments = (char **)malloc(sizeof(char *) * 3);
    if (!data.arguments)
    {
        free_envp(data.envp);
        return (1); // Handle memory allocation failure
    }
    data.arguments[0] = ft_strdup("ft_export");
    data.arguments[1] = ft_strdup("PATH=/usr/local/bin");
    data.arguments[2] = NULL;
    ft_export(&data);
    free(data.arguments[0]);
    free(data.arguments[1]);
    free(data.arguments);

    // Invalid argument: should print error message
    data.arguments = (char **)malloc(sizeof(char *) * 3);
    if (!data.arguments)
    {
        free_envp(data.envp);
        return (1); // Handle memory allocation failure
    }
    data.arguments[0] = ft_strdup("ft_export");
    data.arguments[1] = ft_strdup("1INVALID=argument");
    data.arguments[2] = NULL;
    ft_export(&data);
    free(data.arguments[0]);
    free(data.arguments[1]);
    free(data.arguments);

    // Cleanup
    free_envp(data.envp);
    return (0);
}
