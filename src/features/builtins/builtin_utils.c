/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:15:23 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/20 22:48:11 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the given command is a shell builtin.
 *
 * This function compares the input command string against a list of known
 * shell builtin commands ("cd", "echo", "env", "exit", "export", "pwd",
 * "unset"). It returns a non-zero value if the command matches any of these
 * builtins, otherwise returns 0.
 *
 * @param cmd The command string to check.
 *
 * @return int Non-zero if the command is a builtin, 0 otherwise.
 */
int	is_builtin(
	t_cmd *cmd)
{
	return (ft_strncmp(cmd->argv[0], "cd\0", 3) == 0
		|| ft_strncmp(cmd->argv[0], "echo\0", 5) == 0
		|| (ft_strncmp(cmd->argv[0], "env\0", 4) == 0 && cmd->argc == 1)
		|| ft_strncmp(cmd->argv[0], "exit\0", 5) == 0
		|| ft_strncmp(cmd->argv[0], "export\0", 7) == 0
		|| ft_strncmp(cmd->argv[0], "printenv\0", 9) == 0
		|| ft_strncmp(cmd->argv[0], "pwd\0", 4) == 0
		|| ft_strncmp(cmd->argv[0], "unset\0", 6) == 0);
}
