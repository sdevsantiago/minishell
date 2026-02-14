/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 13:12:58 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "errors.h"
#include <errno.h>

static uint8_t	resolve_execve_status(void)
{
	if (errno == ENOENT)
		return (127);
	if (errno == EACCES || errno == ENOEXEC || errno == EISDIR)
		return (126);
	return (EXIT_FAILURE);
}

static uint8_t	execute_builtin(
	const t_command *command,
	t_minishell *minishell
)
{
	const t_builtin_func	builtin
		= ft_hashmap_get(minishell->builtins, command->argv[0]);

	return (builtin(*command, minishell));
}

static void	handle_execve_error(
	const t_command *command,
	char **envp
)
{
	uint8_t	exit_status;
	size_t	i;

	exit_status = resolve_execve_status();
	i = 0;
	while (envp[i] != NULL)
		free(envp[i++]);
	free(envp);
	perror(command->path);
	exit(exit_status);
}

static void	execute_external_command(
	const t_command *command,
	t_minishell *minishell
)
{
	char	**envp;

	envp = get_envp(minishell);
	if (envp == NULL)
		return (malloc_error(), exit(EXIT_FAILURE));
	execve(command->path, command->argv, envp);
	handle_execve_error(command, envp);
}

uint8_t	executor_execute_command(
	t_command *command,
	t_minishell *minishell
)
{
	if (command == NULL || command->argv == NULL || command->argv[0] == NULL)
		return (EXIT_SUCCESS);
	if (executor_is_builtin_command(command, minishell))
		return (execute_builtin(command, minishell));
	if (command->path != NULL)
		free(command->path);
	command->path = executor_resolve_command_path(command, minishell);
	if (command->path == NULL)
		return (command_not_found_error(command->argv[0]), 127);
	execute_external_command(command, minishell);
	return (EXIT_FAILURE);
}
