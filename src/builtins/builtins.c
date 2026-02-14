/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:04:57 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/08 19:51:38 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static uint8_t	register_builtin(
	t_minishell *minishell,
	const char *name,
	t_builtin_func builtin
)
{
	char	*key;

	key = ft_strdup(name);
	if (key == NULL)
		return (0);
	ft_hashmap_put(minishell->builtins, key, builtin);
	if (!ft_hashmap_contains_key(minishell->builtins, name))
	{
		free(key);
		return (0);
	}
	return (1);
}

uint8_t	set_builtins(
	t_minishell *minishell
) {
	minishell->builtins
		= ft_hashmap_new(7, ft_hashmap_hashstr, ft_hashmap_strcmp);
	if (minishell->builtins == NULL)
		return (0);
	if (!register_builtin(minishell, "cd", builtin_cd)
		|| !register_builtin(minishell, "echo", builtin_echo)
		|| !register_builtin(minishell, "env", builtin_env)
		|| !register_builtin(minishell, "exit", builtin_exit)
		|| !register_builtin(minishell, "export", builtin_export)
		|| !register_builtin(minishell, "pwd", builtin_pwd)
		|| !register_builtin(minishell, "unset", builtin_unset))
	{
		ft_hashmap_clear_keys(&minishell->builtins);
		return (0);
	}
	return (1);
}

uint8_t	is_builtin(
	const char *command_name,
	t_minishell *minishell
) {
	if (command_name == NULL || minishell == NULL
		|| minishell->builtins == NULL)
		return (0);
	return (ft_hashmap_contains_key(minishell->builtins, command_name));
}
