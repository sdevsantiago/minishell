/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_fields.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:15:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 13:15:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand_internal.h"

static t_fields_ctx	init_fields_ctx(
	t_list **fields,
	char **current,
	t_field_state *state
)
{
	t_fields_ctx	ctx;

	ctx.fields = fields;
	ctx.current = current;
	ctx.touched = &state->touched;
	ctx.in_single_quote = &state->in_single_quote;
	ctx.in_double_quote = &state->in_double_quote;
	return (ctx);
}

static bool	finish_word_fields(
	t_fields_ctx ctx
)
{
	if (*ctx.in_single_quote || *ctx.in_double_quote)
	{
		ft_lstclear(ctx.fields, free);
		free(*ctx.current);
		syntax_error_unexpected_token(NULL);
		ctx.minishell->exit_status = 2;
		return (false);
	}
	if ((*ctx.touched || (*ctx.current)[0] != '\0')
		&& !parser_fields_push_field(ctx))
		return (false);
	free(*ctx.current);
	return (true);
}

static bool	process_word_fields(
	const char *word,
	t_fields_ctx ctx
)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (!parser_fields_step(word, &i, ctx))
			return (false);
	}
	return (true);
}

static bool	set_empty_word_field(
	t_list **fields,
	t_minishell *minishell
)
{
	t_list	*node;

	node = ft_lstnew(ft_strdup(""));
	if (node == NULL || node->content == NULL)
		return (free(node), parser_expand_malloc_error(minishell), false);
	*fields = node;
	return (true);
}

bool	parser_expand_word_fields(
	const char *word,
	t_minishell *minishell,
	bool expand_vars,
	t_list **fields
)
{
	char			*current;
	t_field_state	state;
	t_fields_ctx	ctx;

	*fields = NULL;
	if (word[0] == '\0')
		return (set_empty_word_field(fields, minishell));
	current = ft_strdup("");
	if (current == NULL)
		return (parser_expand_malloc_error(minishell), false);
	state.touched = false;
	state.in_single_quote = false;
	state.in_double_quote = false;
	ctx = init_fields_ctx(fields, &current, &state);
	ctx.minishell = minishell;
	ctx.expand_vars = expand_vars;
	if (!process_word_fields(word, ctx))
		return (ft_lstclear(fields, free), free(current), false);
	return (finish_word_fields(ctx));
}
