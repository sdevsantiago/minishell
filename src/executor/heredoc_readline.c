/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:20:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/15 00:20:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_internal.h"
#include "variables.h"
#include <errno.h>

static bool	append_char(char **line, size_t *len, char c)
{
	char	*new_line;
	size_t	i;

	new_line = (char *)malloc(*len + 2);
	if (new_line == NULL)
		return (free(*line), *line = NULL, false);
	i = 0;
	while (i < *len)
	{
		new_line[i] = (*line)[i];
		i++;
	}
	new_line[*len] = c;
	new_line[*len + 1] = '\0';
	free(*line);
	*line = new_line;
	(*len)++;
	return (true);
}

static char	*read_line_stdin(void)
{
	char	*line;
	char	c;
	size_t	len;
	ssize_t	nread;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	len = 0;
	errno = 0;
	nread = read(STDIN_FILENO, &c, 1);
	while (nread > 0)
	{
		if (c == '\n')
			return (line);
		if (!append_char(&line, &len, c))
			return (NULL);
		nread = read(STDIN_FILENO, &c, 1);
	}
	if (nread == -1 && errno == EINTR)
		return (line);
	if (len > 0)
		return (line);
	return (free(line), NULL);
}

char	*executor_heredoc_read_line(t_minishell *minishell)
{
	char	*prompt;
	char	*line;
	size_t	len;

	if (!isatty(STDIN_FILENO))
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (NULL);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		return (line);
	}
	prompt = get_var("PS2", minishell);
	if (prompt == NULL)
		prompt = DEFAULT_PS2;
	if (write(STDOUT_FILENO, prompt, ft_strlen(prompt)) == -1)
		return (NULL);
	return (read_line_stdin());
}
