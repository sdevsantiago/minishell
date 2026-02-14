/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:00:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/13 00:00:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "signals_internal.h"

int	g_signal = 0;

static void	sigint_handler_interactive(int signal)
{
	g_signal = signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	minishell_set_interactive_signals(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = sigint_handler_interactive;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}

void	minishell_set_execution_signals(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = SIG_IGN;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

bool	minishell_consume_sigint(void)
{
	if (g_signal != SIGINT)
		return (false);
	g_signal = 0;
	return (true);
}
