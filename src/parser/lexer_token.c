/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:12:49 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/13 21:12:49 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_type	get_token_type(
	const char *str
)
{
	if (str == NULL || str[0] == '\0')
		return (TOKEN_WORD);
	if (str[0] == '|')
		return (TOKEN_PIPE);
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIRECT_IN);
	}
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (TOKEN_APPEND);
		return (TOKEN_REDIRECT_OUT);
	}
	return (TOKEN_WORD);
}

t_token	*token_new(
	t_token_type type,
	char *text
)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = text;
	if (token->type == TOKEN_WORD && token->value == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

void	token_clear(
	t_token *token
)
{
	if (token != NULL)
	{
		free(token->value);
		free(token);
	}
}
