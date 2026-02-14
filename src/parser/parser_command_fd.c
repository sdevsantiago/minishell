/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:40:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 16:40:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <limits.h>

static bool	parse_io_number(const char *value, int *io_number)
{
	long	number;
	size_t	i;

	if (value == NULL || value[0] == '\0')
		return (false);
	number = 0;
	i = 0;
	while (value[i] != '\0')
	{
		if (!ft_isdigit(value[i]))
			return (false);
		if (number > (INT_MAX - (value[i] - '0')) / 10)
			return (false);
		number = (number * 10) + (value[i] - '0');
		i++;
	}
	*io_number = (int)number;
	return (true);
}

bool	parser_token_is_fd_prefix(
	t_list *token_node,
	int *io_number
)
{
	t_token	*token;
	t_token	*next_token;

	if (token_node == NULL || token_node->next == NULL)
		return (false);
	token = (t_token *)token_node->content;
	next_token = (t_token *)token_node->next->content;
	if (token == NULL || next_token == NULL || token->type != TOKEN_WORD
		|| !is_redirection(next_token))
		return (false);
	return (parse_io_number(token->value, io_number));
}
