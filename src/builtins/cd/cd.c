/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 00:05:22 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/02 20:07:29 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char		*get_path(t_command cmd, t_minishell *msh);
static u_int8_t	handle_error(t_command cmd, t_minishell *msh, char *path);

u_int8_t	builtin_cd(
	t_command cmd,
	t_minishell *msh
) {
	char	*path;
	char	old_pwd[PATH_MAX];

	if (cmd.argc > 2)
	{
		ft_eputendl("minishell: cd: too many arguments");
		return (2);
	}
	else
		path = get_path(cmd, msh);
	getcwd(old_pwd, PATH_MAX);
	if (chdir(path) == -1)
		return (handle_error(cmd, msh, path));
	set_env("OLDPWD", old_pwd, msh);
	return (EXIT_SUCCESS);
}

static char	*get_path(
	t_command cmd,
	t_minishell *msh
) {
	char	*path;

	if (cmd.argc == 1)
		path = get_env("HOME", msh);
	else if (ft_strcmp(cmd.argv[1], "-") == 0)
		path = get_env("OLDPWD", msh);
	else
		path = cmd.argv[1];
	return (path);
}

static u_int8_t	handle_error(
	t_command cmd,
	t_minishell *msh,
	char *path
){
	u_int8_t	exit_code;

	(void)msh;
	exit_code = 0;
	if (access(path, F_OK) != -1)
		// No such file or directory
		exit_code = 1;
	else if (access(path, X_OK) == -1)
		// Permission denied
		exit_code = 2;
	perror(cmd.argv[0]);
	return (exit_code);
}
