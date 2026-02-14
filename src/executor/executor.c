/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:10:47 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 13:10:43 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	init_exec_state(
	t_exec_state *state,
	t_list *command_list
)
{
	state->exit_status = EXIT_SUCCESS;
	state->pipeline.prev_read_fd = -1;
	state->current_command = command_list;
	state->last_child_pid = -1;
}

static bool	fork_current_command(
	t_exec_state *state,
	t_minishell *minishell
)
{
	pid_t	pid;

	pid = fork();
	if (pid == FORK_ERROR)
		return (perror("fork"), state->exit_status = EXIT_FAILURE, false);
	if (pid == 0)
		executor_child_process(state->current_command, &state->pipeline,
			minishell);
	state->last_child_pid = pid;
	return (true);
}

static void	run_command_in_parent(
	t_exec_state *state,
	t_minishell *minishell
)
{
	t_command	*command;
	int			saved_stdin;
	int			saved_stdout;
	int			saved_stderr;

	command = state->current_command->content;
	if (!executor_apply_redirections(command, &saved_stdin, &saved_stdout,
			&saved_stderr))
		state->exit_status = EXIT_FAILURE;
	else
		state->exit_status = executor_execute_command(command, minishell);
	executor_restore_redirections(saved_stdin, saved_stdout, saved_stderr);
}

static bool	run_current_command(
	t_exec_state *state,
	t_minishell *minishell
)
{
	bool		should_fork;

	if (executor_create_pipe_if_needed(state->current_command,
			&state->pipeline) == PIPE_ERROR)
		return (state->exit_status = EXIT_FAILURE, false);
	should_fork = executor_is_fork_required(state->current_command,
			&state->pipeline, minishell);
	if (should_fork)
	{
		if (!fork_current_command(state, minishell))
			return (false);
	}
	else
		run_command_in_parent(state, minishell);
	executor_parent_cleanup(state->current_command, &state->pipeline);
	state->current_command = state->current_command->next;
	return (true);
}

uint8_t	execute(
	t_list *command_list,
	t_minishell *minishell
)
{
	t_exec_state	state;

	init_exec_state(&state, command_list);
	if (!executor_prepare_heredocs(command_list, minishell, &state.exit_status))
	{
		minishell->exit_status = state.exit_status;
		ft_lstclear(&command_list, (void (*)(void *))executor_cmdfree);
		return (state.exit_status);
	}
	minishell_set_execution_signals();
	while (state.current_command)
	{
		if (!run_current_command(&state, minishell))
			break ;
	}
	if (state.last_child_pid > 0)
		state.exit_status = executor_wait_for_children(state.last_child_pid);
	minishell_set_interactive_signals();
	minishell->exit_status = state.exit_status;
	ft_lstclear(&command_list, (void (*)(void *))executor_cmdfree);
	return (state.exit_status);
}
