/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:40:35 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/04 00:28:53 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_local(char const *cmd);
static int	is_builtin(char const *cmd);
static char	*resolve_cmd_path(char const *cmd, char const *path);

/**
 * @brief Parses a command line string into a t_cmd structure.
 *
 * This function takes a command line string and a pointer to the minishell
 * context, splits the line into arguments, and fills a t_cmd structure with
 * the command path, argument vector, and argument count.
 *
 * @param line      The input command line string to parse.
 * @param minishell Pointer to the minishell context.
 *
 * @return t_cmd The parsed command structure containing the command path,
 *               argument vector, and argument count.
 *
 * @note The string array cmd.argv must be freed after the command has been
 *       executed.
 */
t_cmd	parse_cmd(
	char *line,
	t_minishell *minishell)
{
	t_cmd	cmd;
	char	*abs_path;

	(void)minishell;
	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.argv = ft_split(line, ' ');
	// skip check for the moment
	cmd.argc = 0;
	while (cmd.argv[cmd.argc])
		cmd.argc++;
	if (!is_local(cmd.argv[0]) && !is_builtin(cmd.argv[0]))
	{
		abs_path = resolve_cmd_path(cmd.argv[0], getenv("PATH"));
		if (abs_path)
		{
			free(cmd.argv[0]);
			cmd.argv[0] = abs_path;
		}
	}
	return (cmd);
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
static int	is_local(
	char const *cmd)
{
	return (cmd[0] == '.' && cmd[1] == '/');
}

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
static int	is_builtin(
	char const *cmd)
{
	return (!ft_strncmp(cmd, "cd\0", 3)
		|| !ft_strncmp(cmd, "echo\0", 5)
		|| !ft_strncmp(cmd, "env\0", 4)
		|| !ft_strncmp(cmd, "exit\0", 5)
		|| !ft_strncmp(cmd, "export\0", 7)
		|| !ft_strncmp(cmd, "pwd\0", 4)
		|| !ft_strncmp(cmd, "unset\0", 6));
}

static char	*resolve_cmd_path(char const *cmd, char const *path)
{
	char		*abs_path;
	char const	**path_splitted = (char const **)ft_split(path, ':');
	size_t		i;

	abs_path = NULL;
	i = 0;
	while (path_splitted[i])
	{
		abs_path = ft_strjoin_mul(
			3, (char *)path_splitted[i], "/", (char *)cmd);
		if (access(abs_path, F_OK) != -1)
			break ;
		i++;
	}
	ft_free_split((char **)path_splitted);
	return (abs_path);
}
