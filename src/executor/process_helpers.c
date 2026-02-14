/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/11 00:00:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	set_signal_exit_status(
	int status,
	uint8_t *exit_status
)
{
	if (WTERMSIG(status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (WTERMSIG(status) == SIGQUIT)
	{
		if (WCOREDUMP(status))
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		else
			write(STDERR_FILENO, "Quit\n", 5);
	}
	*exit_status = 128 + WTERMSIG(status);
}

static void	set_last_child_status(
	int status,
	uint8_t *exit_status
)
{
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		set_signal_exit_status(status, exit_status);
}

void	executor_child_process(
	t_list *current_command,
	t_pipeline *pipeline,
	t_minishell *minishell
)
{
	uint8_t		exit_status;
	t_command	*command;

	command = current_command->content;
	minishell_set_child_signals();
	executor_setup_child_input(pipeline);
	executor_setup_child_output(current_command, pipeline);
	if (!executor_apply_redirections(command, NULL, NULL, NULL))
		exit(EXIT_FAILURE);
	exit_status = executor_execute_command(command, minishell);
	exit(exit_status);
}

void	executor_parent_cleanup(
	t_list *current_command,
	t_pipeline *pipeline
)
{
	if (pipeline->prev_read_fd != -1)
		close(pipeline->prev_read_fd);
	if (current_command->next)
	{
		close(pipeline->pipefd[WRITE_PIPE]);
		pipeline->prev_read_fd = pipeline->pipefd[READ_PIPE];
	}
	else
		pipeline->prev_read_fd = -1;
}

uint8_t	executor_wait_for_children(
	pid_t last_child_pid
)
{
	uint8_t	exit_status;
	int		status;
	pid_t	pid;

	exit_status = EXIT_SUCCESS;
	pid = wait(&status);
	while (last_child_pid > 0 && pid > 0)
	{
		if (pid == last_child_pid)
			set_last_child_status(status, &exit_status);
		pid = wait(&status);
	}
	return (exit_status);
}
