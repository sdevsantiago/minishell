/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:50:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 17:50:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_internal.h"
#include <errno.h>
#include "variables.h"

static char	*build_tmp_path(unsigned int id)
{
	char	*suffix;
	char	*path;

	suffix = ft_uitoa(id);
	if (suffix == NULL)
		return (errno = ENOMEM, NULL);
	path = ft_strnjoin(2, "/tmp/minishell_heredoc_", suffix);
	free(suffix);
	if (path == NULL)
		return (errno = ENOMEM, NULL);
	return (path);
}

int	executor_heredoc_open_tmp(char **path_out)
{
	static unsigned int	counter;
	char				*path;
	unsigned int		attempts;
	int					fd;

	attempts = 0;
	while (attempts++ < 10000)
	{
		path = build_tmp_path(counter++);
		if (path == NULL)
			return (-1);
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0600);
		if (fd != -1)
			return (*path_out = path, fd);
		free(path);
		if (errno != EEXIST)
			return (-1);
	}
	errno = EEXIST;
	return (-1);
}

void	executor_heredoc_discard_tmp(int fd, char *path)
{
	if (fd >= 0)
		close(fd);
	if (path != NULL)
	{
		unlink(path);
		free(path);
	}
}

bool	executor_heredoc_finalize_tmp(t_redirection *rd, int fd, char *path,
		uint8_t *exit_status)
{
	if (close(fd) == -1)
		return (executor_heredoc_discard_tmp(-1, path), perror("close"),
			*exit_status = EXIT_FAILURE, false);
	free(rd->target);
	rd->target = path;
	rd->heredoc_ready = true;
	return (true);
}
