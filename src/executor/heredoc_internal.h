/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:50:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 17:50:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_INTERNAL_H
# define HEREDOC_INTERNAL_H

# include "executor.h"

char	*executor_heredoc_read_line(t_minishell *minishell);
int		executor_heredoc_open_tmp(char **path_out);
void	executor_heredoc_discard_tmp(int fd, char *path);
bool	executor_heredoc_finalize_tmp(t_redirection *rd, int fd, char *path,
			uint8_t *exit_status);
bool	executor_heredoc_fill_tmp(int fd, t_redirection *rd,
			t_minishell *minishell, uint8_t *exit_status);

#endif
