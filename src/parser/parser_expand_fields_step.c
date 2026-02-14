/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_fields_step.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:12:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 14:12:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand_internal.h"

static bool	handle_quote_char(
	const char *word,
	size_t *i,
	t_fields_ctx ctx
)
{
	if (word[*i] == '\'' && !*ctx.in_double_quote)
	{
		*ctx.in_single_quote = !*ctx.in_single_quote;
		*ctx.touched = true;
		(*i)++;
		return (true);
	}
	if (word[*i] == '\"' && !*ctx.in_single_quote)
	{
		*ctx.in_double_quote = !*ctx.in_double_quote;
		*ctx.touched = true;
		(*i)++;
		return (true);
	}
	return (false);
}

static bool	skip_dollar_quote_prefix(
	const char *word,
	size_t *i,
	t_fields_ctx ctx
)
{
	if (word[*i] == '$' && !*ctx.in_single_quote && !*ctx.in_double_quote
		&& word[*i + 1] != '\0'
		&& (word[*i + 1] == '\'' || word[*i + 1] == '\"'))
	{
		(*i)++;
		return (true);
	}
	return (false);
}

static bool	expand_dollar_token(
	const char *word,
	size_t *i,
	t_fields_ctx ctx,
	bool *handled
)
{
	char	*expanded;

	*handled = false;
	if (word[*i] != '$' || *ctx.in_single_quote || !ctx.expand_vars)
		return (true);
	*handled = true;
	expanded = parser_expand_variable(word, i, ctx.minishell);
	if (expanded == NULL)
		return (false);
	if (!*ctx.in_double_quote
		&& !parser_fields_expand_unquoted_value(ctx, expanded))
		return (free(expanded), false);
	if (*ctx.in_double_quote && !parser_fields_append_text(ctx.current,
			expanded, ctx.minishell))
		return (free(expanded), false);
	if (*ctx.in_double_quote && expanded[0] != '\0')
		*ctx.touched = true;
	free(expanded);
	return (true);
}

bool	parser_fields_step(
	const char *word,
	size_t *i,
	t_fields_ctx ctx
)
{
	char	value[2];
	bool	handled;

	if (handle_quote_char(word, i, ctx))
		return (true);
	if (!parser_fields_handle_backslash(word, i, ctx, &handled))
		return (false);
	if (handled)
		return (true);
	if (!parser_fields_expand_tilde(word, i, ctx, &handled))
		return (false);
	if (handled)
		return (true);
	if (skip_dollar_quote_prefix(word, i, ctx))
		return (true);
	if (!expand_dollar_token(word, i, ctx, &handled))
		return (false);
	if (handled)
		return (true);
	value[0] = word[(*i)++];
	value[1] = '\0';
	if (!parser_fields_append_text(ctx.current, value, ctx.minishell))
		return (false);
	*ctx.touched = true;
	return (true);
}
