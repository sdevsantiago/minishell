/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:40:35 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/05 19:56:15 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * @todo Manage double quote
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
	if (!is_local(cmd.argv[0]) && !is_absolutepath(cmd.argv[0])
		&& !is_builtin(&cmd))
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

static char	*resolve_cmd_path(char const *cmd, char const *path)
{
	char		*abs_path;
	char const	**path_splitted = (char const **)ft_split(path, ':');
	size_t		i;

	abs_path = NULL;
	i = 0;
	while (path_splitted[i])
	{
		abs_path = ft_strnjoin(
			3, (char *)path_splitted[i], "/", (char *)cmd);
		if (access(abs_path, X_OK) != -1)
			break ;
		free(abs_path);
		abs_path = NULL;
		i++;
	}
	ft_free_split((char **)path_splitted);
	return (abs_path);
}
