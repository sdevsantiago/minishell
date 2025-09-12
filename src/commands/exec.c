/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:24:47 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/05 20:21:27 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(
	t_cmd *cmd,
	char **envp)
{
	if (ft_strncmp(cmd->argv[0], "cd\0", 3) == 0)
		return (cd_builtin(cmd->argc, (char const **)cmd->argv));
	else if (ft_strncmp(cmd->argv[0], "echo\0", 5) == 0)
		return (echo_builtin(cmd->argc, (char const **)cmd->argv));
	// else if (ft_strncmp(cmd->argv[0], "env\0", 4) == 0)
		// return (env_builtin(cmd->argc, (char const **)cmd->argv, envp));
	// else if (ft_strncmp(cmd->argv[0], "exit\0", 5) == 0)
		// return (exit_builtin(cmd->argc, (char const **)cmd->argv));
	else if (ft_strncmp(cmd->argv[0], "export\0", 7) == 0)
		return (export_builtin(cmd->argc, (char const **)cmd->argv, envp));
	else if ((ft_strncmp(cmd->argv[0], "env\0", 4) == 0 && cmd->argc == 1)
		|| ft_strncmp(cmd->argv[0], "printenv\0", 9) == 0)
		return (printenv_builtin(
			cmd->argc, (char const **)cmd->argv, (char const **)envp));
	else if (ft_strncmp(cmd->argv[0], "pwd\0", 4) == 0)
		return (pwd_builtin(cmd->argc, (char const **)cmd->argv));
	else if (ft_strncmp(cmd->argv[0], "unset\0", 6) == 0)
		return (unset_builtin(cmd->argc, (char const **)cmd->argv, envp));
	return (1);
}

int	exec_cmd(
	t_cmd *cmd,
	char **envp)
{
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	pid = fork();
	if (pid == 0)
		exit_code = execve(cmd->argv[0], cmd->argv, envp);
	waitpid(pid, NULL, 0);
	return (exit_code);
}

