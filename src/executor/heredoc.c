/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:50:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 17:50:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_internal.h"
#include "errors.h"

static bool	prepare_heredoc_redirection(t_redirection *rd,
		t_minishell *minishell, uint8_t *exit_status)
{
	char	*path;
	int		fd;

	path = NULL;
	fd = executor_heredoc_open_tmp(&path);
	if (fd == -1)
		return (perror("open"), *exit_status = EXIT_FAILURE, false);
	if (!executor_heredoc_fill_tmp(fd, rd, minishell, exit_status))
		return (executor_heredoc_discard_tmp(fd, path), false);
	return (executor_heredoc_finalize_tmp(rd, fd, path, exit_status));
}

static bool	process_command_heredocs(t_command *command, t_minishell *minishell,
		uint8_t *exit_status)
{
	t_list			*redir_node;
	t_redirection	*rd;

	redir_node = command->redirections;
	while (redir_node != NULL)
	{
		rd = (t_redirection *)redir_node->content;
		if (rd->type == TOKEN_HEREDOC
			&& !prepare_heredoc_redirection(rd, minishell, exit_status))
			return (false);
		redir_node = redir_node->next;
	}
	return (true);
}

bool	executor_prepare_heredocs(t_list *command_list, t_minishell *minishell,
		uint8_t *exit_status)
{
	t_command	*command;

	*exit_status = EXIT_SUCCESS;
	minishell_set_heredoc_signals();
	while (command_list != NULL)
	{
		command = (t_command *)command_list->content;
		if (!process_command_heredocs(command, minishell, exit_status))
			return (minishell_set_interactive_signals(), false);
		command_list = command_list->next;
	}
	minishell_set_interactive_signals();
	return (true);
}
