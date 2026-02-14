/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 23:40:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 23:40:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "signals_internal.h"

static void	sigint_handler_heredoc(int signal)
{
	g_signal = signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	minishell_set_heredoc_signals(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = sigint_handler_heredoc;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}
