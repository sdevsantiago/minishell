/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 06:56:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 06:56:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand_internal.h"

static bool	word_toggle_quotes(
	char c,
	bool *in_single_quote,
	bool *in_double_quote
)
{
	if (c == '\'' && !*in_double_quote)
		return (*in_single_quote = !*in_single_quote, true);
	if (c == '\"' && !*in_single_quote)
		return (*in_double_quote = !*in_double_quote, true);
	return (false);
}

static bool	word_append(
	char **result,
	const char *value,
	t_minishell *minishell
)
{
	char	*joined;

	joined = ft_strnjoin(2, *result, (char *)value);
	if (joined == NULL)
	{
		free(*result);
		*result = NULL;
		return (parser_expand_malloc_error(minishell), false);
	}
	free(*result);
	*result = joined;
	return (true);
}

static bool	word_step(
	const char *word,
	size_t *i,
	t_word_ctx ctx
)
{
	char	*expanded;
	char	value[2];

	if (word_toggle_quotes(word[*i], ctx.in_single_quote, ctx.in_double_quote))
		return ((*i)++, true);
	if (word[*i] == '$' && word[*i + 1] != '\0'
		&& !*ctx.in_single_quote && !*ctx.in_double_quote
		&& (word[*i + 1] == '\'' || word[*i + 1] == '\"'))
		return ((*i)++, true);
	if (word[*i] == '$' && !*ctx.in_single_quote && ctx.expand_vars)
	{
		expanded = parser_expand_variable(word, i, ctx.minishell);
		if (expanded == NULL || !word_append(ctx.result, expanded,
				ctx.minishell))
			return (free(expanded), false);
		return (free(expanded), true);
	}
	value[0] = word[*i];
	value[1] = '\0';
	(*i)++;
	return (word_append(ctx.result, value, ctx.minishell));
}

char	*parser_expand_word(
	const char *word,
	t_minishell *minishell,
	bool expand_vars
)
{
	char	*result;
	size_t	i;
	bool	in_single_quote;
	bool	in_double_quote;

	result = ft_strdup("");
	if (result == NULL)
		return (parser_expand_malloc_error(minishell), NULL);
	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (word[i] != '\0')
	{
		if (!word_step(word, &i, (t_word_ctx){&result, &in_single_quote,
				&in_double_quote, minishell, expand_vars}))
			return (NULL);
	}
	if (in_single_quote || in_double_quote)
		return (free(result), syntax_error_unexpected_token(NULL),
			minishell->exit_status = 2, NULL);
	return (result);
}
