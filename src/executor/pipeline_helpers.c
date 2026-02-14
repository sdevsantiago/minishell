/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/11 00:00:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

int	executor_create_pipe_if_needed(
	t_list *current_command,
	t_pipeline *pipeline
)
{
	if (!current_command->next)
		return (0);
	if (pipe(pipeline->pipefd) == PIPE_ERROR)
		return (perror("pipe"), PIPE_ERROR);
	return (0);
}

bool	executor_is_builtin_command(
	const t_command *command,
	t_minishell *minishell
)
{
	if (command == NULL || command->argv == NULL || command->argv[0] == NULL)
		return (false);
	return (is_builtin(command->argv[0], minishell));
}

bool	executor_is_fork_required(
	t_list *current_command,
	const t_pipeline *pipeline,
	t_minishell *minishell
)
{
	const t_command	*command;

	command = current_command->content;
	return (pipeline->prev_read_fd != -1 || current_command->next != NULL
		|| !executor_is_builtin_command(command, minishell));
}

void	executor_setup_child_input(
	t_pipeline *pipeline
)
{
	if (pipeline->prev_read_fd != -1)
	{
		dup2(pipeline->prev_read_fd, STDIN_FILENO);
		close(pipeline->prev_read_fd);
	}
}

void	executor_setup_child_output(
	t_list *current_command,
	t_pipeline *pipeline
)
{
	if (current_command->next)
	{
		dup2(pipeline->pipefd[WRITE_PIPE], STDOUT_FILENO);
		close(pipeline->pipefd[READ_PIPE]);
		close(pipeline->pipefd[WRITE_PIPE]);
	}
}
