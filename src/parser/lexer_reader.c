/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:13:23 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/13 21:13:23 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static inline bool	is_meta(char c);

t_token	*read_token(
	t_token_type type,
	const char *line,
	size_t *i
)
{
	const size_t	start = *i;
	size_t			end;

	while (is_meta(line[*i]))
		(*i)++;
	end = *i;
	while (ft_isspace(line[*i]))
		(*i)++;
	return (token_new(type, ft_substr(line, start, end - start)));
}

t_token	*read_word(
	const char *line,
	size_t *i
)
{
	const size_t	start = *i;
	bool			in_single_quote;
	bool			in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	while (line[*i] != '\0')
	{
		if (line[*i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (line[*i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote
			&& (isspace(line[*i]) || is_meta(line[*i])))
			break ;
		(*i)++;
	}
	return (token_new(TOKEN_WORD, ft_substr(line, start, *i - start)));
}

static inline bool	is_meta(
	char c
)
{
	return (c == '|' || c == '<' || c == '>');
}
