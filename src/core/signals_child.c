/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:20:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 18:20:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	minishell_set_child_signals(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = SIG_DFL;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}
