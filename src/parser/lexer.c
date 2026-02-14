/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:56:41 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/11 02:06:36 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "parser.h"

static t_token	*tokenize(const char *line, size_t *start);

/**
 * @brief Converts a command line string into a list of tokens.
 * 
 * @return A list of tokens or NULL on error.
 */
t_list	*lex(
	const char *line
)
{
	t_list	*tokens;
	t_token	*token;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		token = tokenize(line, &i);
		ft_lstadd_back(&tokens, ft_lstnew(token));
		if (token == NULL)
		{
			ft_lstclear(&tokens, (void (*)(void *))token_clear);
			return (NULL);
		}
	}
	return (tokens);
}

/**
 * @return A new token or NULL on error.
 */
static t_token	*tokenize(
	const char *line,
	size_t *start
)
{
	t_token			*token;
	t_token_type	type;

	if (line == NULL || line[*start] == '\0')
		return (NULL);
	type = get_token_type(line + *start);
	if (type != TOKEN_WORD)
		token = read_token(type, line, start);
	else
		token = read_word(line, start);
	return (token);
}
