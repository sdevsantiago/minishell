/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:09:23 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 13:03:15 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"

void	handle_sigint_status(
	t_minishell *minishell
)
{
	if (!minishell_consume_sigint())
		return ;
	minishell->exit_status = 130;
}

bool	handle_eof(
	char *line,
	t_minishell *minishell
)
{
	if (line != NULL)
		return (false);
	if (isatty(STDIN_FILENO))
		ft_putendl("exit");
	free(line);
	minishell->exit = true;
	return (true);
}
