/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 22:22:06 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 06:58:05 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	syntax_error_unexpected_token(
	t_token *token
)
{
	char	*cause;

	if (token == NULL)
		cause = "newline";
	else
		cause = token->value;
	ft_eprintf("minishell: syntax error near unexpected token `%s'\n", cause);
}

void	malloc_error(void)
{
	ft_eprintf("minishell: %s\n", strerror(ENOMEM));
}

void	command_not_found_error(
	const char *command
)
{
	ft_eprintf("minishell: %s: command not found\n", command);
}
