/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_fields_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:12:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 14:12:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand_internal.h"

bool	parser_fields_append_text(
	char **current,
	const char *value,
	t_minishell *minishell
)
{
	char	*joined;

	joined = ft_strnjoin(2, *current, (char *)value);
	if (joined == NULL)
	{
		free(*current);
		*current = NULL;
		return (parser_expand_malloc_error(minishell), false);
	}
	free(*current);
	*current = joined;
	return (true);
}

static bool	is_ifs_char(
	char c
)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	parser_fields_push_field(
	t_fields_ctx ctx
)
{
	t_list	*node;

	node = ft_lstnew(*ctx.current);
	if (node == NULL)
	{
		free(*ctx.current);
		*ctx.current = NULL;
		return (parser_expand_malloc_error(ctx.minishell), false);
	}
	ft_lstadd_back(ctx.fields, node);
	*ctx.current = ft_strdup("");
	if (*ctx.current == NULL)
		return (ft_lstclear(ctx.fields, free),
			parser_expand_malloc_error(ctx.minishell), false);
	*ctx.touched = false;
	return (true);
}

static void	skip_ifs(
	const char *expanded,
	size_t *i
)
{
	while (expanded[*i] != '\0' && is_ifs_char(expanded[*i]))
		(*i)++;
}

bool	parser_fields_expand_unquoted_value(
	t_fields_ctx ctx,
	const char *expanded
)
{
	size_t	i;
	char	value[2];

	i = 0;
	while (expanded[i] != '\0')
	{
		if (is_ifs_char(expanded[i]))
		{
			if ((*ctx.touched || (*ctx.current)[0] != '\0')
				&& !parser_fields_push_field(ctx))
				return (false);
			skip_ifs(expanded, &i);
			continue ;
		}
		value[0] = expanded[i];
		value[1] = '\0';
		if (!parser_fields_append_text(ctx.current, value, ctx.minishell))
			return (false);
		*ctx.touched = true;
		i++;
	}
	return (true);
}
