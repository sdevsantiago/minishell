/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 13:16:15 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "variables.h"

static bool	is_path_explicit(
	const char *command_name
)
{
	return (command_name != NULL && ft_strchr(command_name, '/') != NULL);
}

static char	*resolve_path_from_env(
	const char *command_name,
	t_minishell *minishell
)
{
	char	*command_path;
	char	**path_env;
	char	*path_value;
	size_t	i;

	path_value = get_env("PATH", minishell);
	if (path_value == NULL)
		return (NULL);
	path_env = ft_split(path_value, ':');
	if (path_env == NULL)
		return (NULL);
	command_path = NULL;
	i = -1;
	while (command_name[0] != 0 && !command_path && path_env[++i] != NULL)
	{
		command_path = ft_strnjoin(3, path_env[i], "/", command_name);
		if (command_path != NULL && access(command_path, X_OK) != EXIT_SUCCESS)
		{
			free(command_path);
			command_path = NULL;
		}
	}
	ft_free_split(path_env);
	return (command_path);
}

static char	*resolve_explicit_path(
	const char *command_name
)
{
	if (access(command_name, F_OK) != EXIT_SUCCESS)
		return (NULL);
	if (access(command_name, X_OK) != EXIT_SUCCESS)
		return (NULL);
	return (ft_strdup(command_name));
}

char	*executor_resolve_command_path(
	const t_command *command,
	t_minishell *minishell
)
{
	const char	*command_name;

	if (command == NULL || command->argv == NULL || command->argv[0] == NULL)
		return (NULL);
	command_name = command->argv[0];
	if (is_path_explicit(command_name))
		return (resolve_explicit_path(command_name));
	return (resolve_path_from_env(command_name, minishell));
}
