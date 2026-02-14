/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_fields_escape.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:40:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 16:40:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand_internal.h"

static bool	is_backslash_escaped_in_double_quote(
	char c
)
{
	return (c == '$' || c == '\"' || c == '\\');
}

static char	get_escaped_char(
	const char *word,
	size_t *i
)
{
	char	value;

	if (word[*i + 1] == '\0')
		value = word[(*i)++];
	else
	{
		value = word[*i + 1];
		*i += 2;
	}
	return (value);
}

bool	parser_fields_handle_backslash(
	const char *word,
	size_t *i,
	t_fields_ctx ctx,
	bool *handled
)
{
	char	value[2];

	*handled = false;
	if (word[*i] != '\\' || *ctx.in_single_quote)
		return (true);
	if (*ctx.in_double_quote
		&& !is_backslash_escaped_in_double_quote(word[*i + 1]))
		return (true);
	*handled = true;
	value[0] = get_escaped_char(word, i);
	value[1] = '\0';
	if (!parser_fields_append_text(ctx.current, value, ctx.minishell))
		return (false);
	*ctx.touched = true;
	return (true);
}

bool	parser_fields_expand_tilde(
	const char *word,
	size_t *i,
	t_fields_ctx ctx,
	bool *handled
)
{
	char	*home;

	*handled = false;
	if (word[*i] != '~' || *ctx.in_single_quote || *ctx.in_double_quote
		|| *i != 0 || (word[*i + 1] != '\0' && word[*i + 1] != '/'))
		return (true);
	home = get_var("HOME", ctx.minishell);
	if (home == NULL)
		return (true);
	*handled = true;
	(*i)++;
	if (!parser_fields_append_text(ctx.current, home, ctx.minishell))
		return (false);
	*ctx.touched = true;
	return (true);
}
