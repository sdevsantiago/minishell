/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:00:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/12 00:00:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <errno.h>

static int	open_redirection_target(
	const t_redirection *redirection
)
{
	if (redirection->type == TOKEN_REDIRECT_IN)
		return (open(redirection->target, O_RDONLY));
	if (redirection->type == TOKEN_HEREDOC)
		return (open(redirection->target, O_RDONLY));
	if (redirection->type == TOKEN_REDIRECT_OUT)
		return (open(redirection->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redirection->type == TOKEN_APPEND)
		return (open(redirection->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	errno = EINVAL;
	return (-1);
}

static bool	backup_fd_if_needed(
	int io_number,
	int *saved_fd
)
{
	if (saved_fd == NULL || *saved_fd != -1)
		return (true);
	*saved_fd = dup(io_number);
	if (*saved_fd == -1)
		return (perror("dup"), false);
	return (true);
}

static bool	apply_redirection(
	const t_redirection *redirection,
	int *saved_stdin,
	int *saved_stdout,
	int *saved_stderr
)
{
	int	fd;

	if (redirection == NULL || redirection->target == NULL)
		return (false);
	if ((redirection->io_number == STDIN_FILENO
			&& !backup_fd_if_needed(STDIN_FILENO, saved_stdin))
		|| (redirection->io_number == STDOUT_FILENO
			&& !backup_fd_if_needed(STDOUT_FILENO, saved_stdout))
		|| (redirection->io_number == STDERR_FILENO
			&& !backup_fd_if_needed(STDERR_FILENO, saved_stderr)))
		return (false);
	fd = open_redirection_target(redirection);
	if (fd == -1)
		return (perror(redirection->target), false);
	if (dup2(fd, redirection->io_number) == -1)
		return (close(fd), perror("dup2"), false);
	return (close(fd), true);
}

bool	executor_apply_redirections(
	const t_command *command,
	int *saved_stdin,
	int *saved_stdout,
	int *saved_stderr
)
{
	t_list	*node;

	if (saved_stdin != NULL)
		*saved_stdin = -1;
	if (saved_stdout != NULL)
		*saved_stdout = -1;
	if (saved_stderr != NULL)
		*saved_stderr = -1;
	if (command == NULL)
		return (true);
	node = command->redirections;
	while (node != NULL
		&& apply_redirection((t_redirection *)node->content,
			saved_stdin, saved_stdout, saved_stderr))
		node = node->next;
	return (node == NULL);
}

void	executor_restore_redirections(
	int saved_stdin,
	int saved_stdout,
	int saved_stderr
)
{
	if (saved_stdin != -1)
	{
		if (dup2(saved_stdin, STDIN_FILENO) == -1)
			perror("dup2");
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			perror("dup2");
		close(saved_stdout);
	}
	if (saved_stderr != -1)
	{
		if (dup2(saved_stderr, STDERR_FILENO) == -1)
			perror("dup2");
		close(saved_stderr);
	}
}
