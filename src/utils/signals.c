/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:06:16 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/20 19:37:40 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sighandler(int signal, siginfo_t *signal_info, void *context);

void	init_signal(void)
{
	struct sigaction	signal;

	signal.sa_sigaction = sighandler;
	signal.sa_flags = SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	sigaddset(&signal.sa_mask, SIGINT);
	sigaction(SIGINT, &signal, NULL);
}

static void	sighandler(
	int signal,
	siginfo_t *signal_info,
	void *context)
{
	(void)signal_info;
	(void)context;
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
