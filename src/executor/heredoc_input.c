/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:50:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 17:50:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_internal.h"
#include "errors.h"

static bool	write_all(int fd, const char *buffer, size_t len)
{
	size_t	total;
	ssize_t	written;

	total = 0;
	while (total < len)
	{
		written = write(fd, buffer + total, len - total);
		if (written <= 0)
			return (false);
		total += written;
	}
	return (true);
}

static bool	write_heredoc_line(int fd, const char *line)
{
	if (!write_all(fd, line, ft_strlen(line)))
		return (false);
	return (write_all(fd, "\n", 1));
}

static bool	handle_heredoc_line(int fd, char *line, t_redirection *rd,
		t_minishell *minishell)
{
	char	*expanded;

	expanded = line;
	if (rd->heredoc_expand)
	{
		expanded = executor_expand_heredoc_line(line, minishell);
		free(line);
		if (expanded == NULL)
			return (false);
	}
	if (!write_heredoc_line(fd, expanded))
		return (free(expanded), perror("write"), false);
	free(expanded);
	return (true);
}

bool	executor_heredoc_fill_tmp(int fd, t_redirection *rd,
		t_minishell *minishell, uint8_t *exit_status)
{
	char	*line;

	while (1)
	{
		line = executor_heredoc_read_line(minishell);
		if (minishell_consume_sigint())
			return (free(line), *exit_status = 130, false);
		if (line == NULL)
		{
			if (!isatty(STDIN_FILENO))
				minishell->exit = true;
			return (ft_eprintf("minishell: warning: here-document delimited by "
					"end-of-file (wanted `%s')\n", rd->target), true);
		}
		if (ft_strcmp(line, rd->target) == 0)
			return (free(line), true);
		if (!handle_heredoc_line(fd, line, rd, minishell))
			return (*exit_status = EXIT_FAILURE, false);
	}
}
