/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:52:37 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/20 22:15:22 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_absolutepath(
	char const *cmd)
{
	return (cmd[0] == '/');
}

/**
 * @brief Checks if the given command string refers to a local executable.
 *
 * This function determines whether the provided command string starts with
 * "./", which is a common convention for executing local files in Unix-like
 * systems.
 *
 * @param cmd The command string to check.
 *
 * @return 1 if the command starts with "./", 0 otherwise.
 */
int	is_local(
	char const *cmd)
{
	return (cmd[0] == '.' && cmd[1] == '/');
}
