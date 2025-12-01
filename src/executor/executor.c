/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:03:44 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/01 14:08:47 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char		*solve_path(char *cmd_name, t_minishell *msh);
static u_int8_t	path_is_solved(char *cmd_name);
static void		handle_child(t_command *cmd, t_minishell *msh);
static void		handle_parent(pid_t child_pid, t_command *cmd, t_minishell *msh);

u_int8_t	execute(
	t_command cmd,
	t_minishell *msh
){
	pid_t	child_pid;

	cmd.path = solve_path(cmd.argv[0], msh);
	if (!cmd.path)
	{
		// command not found
		ft_eprintf("minishell: %s: command not found\n", cmd.argv[0]);
		return (msh->exit_status = 127, msh->exit_status);
	}
	if (access(cmd.path, X_OK) != EXIT_SUCCESS)
	{
		// permission denied
		ft_eputstr("minishell: ");
		perror(cmd.path);
		return (msh->exit_status = 126, msh->exit_status);
	}
	child_pid = fork();
	if (child_pid == -1)
		perror("minishell");
	else if (child_pid == 0)
		handle_child(&cmd, msh);
	else
		handle_parent(child_pid, &cmd, msh);
	return (msh->exit_status);
}

static char	*solve_path(
	char *cmd_name,
	t_minishell *msh
){
	char	*cmd_path;
	char	**path;
	size_t	i;

	if (path_is_solved(cmd_name))
		// return a copy to avoid double free on parent
		return (ft_strdup(cmd_name));
	path = ft_split(get_env("PATH", msh), COLON);
	if (!path)
		return (NULL);
	cmd_path = NULL;
	i = -1;
	while (!cmd_path && path[++i])
	{
		cmd_path = ft_strnjoin(3, path[i], "/", cmd_name);
		if (!cmd_path)
			return (NULL);
		/**
		 * If a command exists but user has no execution permission
		 * the command is shown as non existant instead of showing the
		 * last ocurrence found
		 *
		 * TLDR:	bash shows 'Permission denied'
		 * 			and minishell 'command not found'
		 *
		 * TEST:	execute an existing command without permission to do so
		 */
		if (access(cmd_path, X_OK) != EXIT_SUCCESS)
			ft_free((void **)&cmd_path);
	}
	ft_free_split((char **)path);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

static u_int8_t	path_is_solved(
	char *cmd_name
){
	return (ft_strncmp(cmd_name, "/", 1) == 0
		|| (cmd_name[1] && ft_strncmp(cmd_name, "./", 2) == 0)
		|| (cmd_name[2] && ft_strncmp(cmd_name, "../", 3) == 0)
	);
}

static void	handle_child(
	t_command *cmd,
	t_minishell *msh
){
	char	**envp;

	envp = get_envp(msh);
	execve(cmd->path, cmd->argv, envp);
	free_envp(envp);
}

static void	handle_parent(
	pid_t child_pid,
	t_command *cmd,
	t_minishell *msh
){
	if (waitpid(child_pid, (int *)&msh->exit_status, 0) == EXIT_SUCCESS)
	{
		// handle success
	}
	else
	{
		// handle error
	}
	ft_free((void **)&cmd->path);
	ft_free_split(cmd->argv);
}
