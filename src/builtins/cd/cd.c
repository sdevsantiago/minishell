/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 00:05:22 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/31 01:38:14 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static u_int8_t	handle_error(t_command cmd, t_minishell *msh, char *path);

u_int8_t	builtin_cd(
	t_command cmd,
	t_minishell *msh
){
	char	*path;

	if (cmd.argc > 2)
	{
		ft_eputendl("minishell: cd: too many arguments");
		return (2);
	}
	else if (cmd.argc == 1)
		path = getenv("HOME");
	else
		path = cmd.argv[1];
	if (chdir(path) == -1)
		return (handle_error(cmd, msh, path));
	return (EXIT_SUCCESS);
}

static u_int8_t	handle_error(
	t_command cmd,
	t_minishell *msh,
	char *path
){
	u_int8_t	exit_code;

	if (access(path, F_OK) != -1)
		// No such file or directory
		exit_code = 1;
	else if (access(path, X_OK) == -1)
		// Permission denied
		exit_code = 2;
	perror(cmd.argv[0]);
	return (exit_code);
}
