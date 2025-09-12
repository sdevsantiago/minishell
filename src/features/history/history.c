/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:06:47 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/21 14:39:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_read_history(
	const char *hist_file)
{
	int		fd;
	char	*line;

	fd = open(hist_file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		add_history(line);
		free(&line);
		line = get_next_line(fd);
	}
	if (line)
		ft_free(&line);
	close(fd);
}

void	ms_write_history(
	const char *hist_file)
{
	
}
