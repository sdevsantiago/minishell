/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 00:05:22 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/01 14:11:32 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static uint8_t	handle_error(void);
static void		update_pwd_vars(t_minishell *msh, char *oldpwd);
static char		*get_path_from_env(
					t_minishell *msh,
					const char *env_name,
					const char *error,
					uint8_t *status
					);
static char		*resolve_cd_path(
					t_command cmd,
					t_minishell *msh,
					uint8_t *status
					);

uint8_t	builtin_cd(
	t_command cmd,
	t_minishell *msh
){
	char	*path;
	char	*oldpwd;
	uint8_t	status;
	bool	show_pwd;

	path = resolve_cd_path(cmd, msh, &status);
	if (status != EXIT_SUCCESS)
		return (status);
	show_pwd = (cmd.argc == 2 && ft_strcmp(cmd.argv[1], "-") == 0);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(oldpwd);
		return (handle_error());
	}
	update_pwd_vars(msh, oldpwd);
	if (show_pwd && get_env("PWD", msh) != NULL)
		ft_putendl(get_env("PWD", msh));
	free(oldpwd);
	return (EXIT_SUCCESS);
}

static uint8_t	handle_error(void)
{
	perror("minishell: cd");
	return (EXIT_FAILURE);
}

static void	update_pwd_vars(
	t_minishell *msh,
	char *oldpwd
){
	char	*newpwd;

	if (oldpwd != NULL)
		set_env("OLDPWD", oldpwd, msh);
	newpwd = getcwd(NULL, 0);
	if (newpwd != NULL)
	{
		set_env("PWD", newpwd, msh);
		free(newpwd);
	}
}

static char	*resolve_cd_path(
	t_command cmd,
	t_minishell *msh,
	uint8_t *status
){
	if (cmd.argc > 2)
	{
		ft_eputendl("minishell: cd: too many arguments");
		*status = EXIT_FAILURE;
		return (NULL);
	}
	if (cmd.argc == 2 && ft_strcmp(cmd.argv[1], "-") == 0)
		return (get_path_from_env(msh, "OLDPWD",
				"minishell: cd: OLDPWD not set", status));
	if (cmd.argc == 1)
		return (get_path_from_env(msh, "HOME",
				"minishell: cd: HOME not set", status));
	*status = EXIT_SUCCESS;
	return (cmd.argv[1]);
}

static char	*get_path_from_env(
	t_minishell *msh,
	const char *env_name,
	const char *error,
	uint8_t *status
){
	char	*path;

	path = get_env(env_name, msh);
	if (path == NULL)
	{
		ft_eputendl((char *)error);
		*status = EXIT_FAILURE;
		return (NULL);
	}
	*status = EXIT_SUCCESS;
	return (path);
}
