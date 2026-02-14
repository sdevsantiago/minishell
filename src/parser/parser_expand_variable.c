/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 06:56:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 06:56:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand_internal.h"

void	parser_expand_malloc_error(
	t_minishell *minishell
)
{
	minishell->exit = true;
	malloc_error();
}

static bool	is_var_char(
	char c
)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*dup_or_error(
	const char *value,
	t_minishell *minishell
)
{
	char	*dup;

	dup = ft_strdup(value);
	if (dup == NULL)
		return (parser_expand_malloc_error(minishell), NULL);
	return (dup);
}

static char	*expand_named_variable(
	const char *word,
	size_t *i,
	t_minishell *minishell
)
{
	char	*name;
	char	*value;
	size_t	start;

	start = *i;
	while (word[*i] != '\0' && is_var_char(word[*i]))
		(*i)++;
	name = ft_substr(word, start, *i - start);
	if (name == NULL)
		return (parser_expand_malloc_error(minishell), NULL);
	value = get_var(name, minishell);
	free(name);
	if (value == NULL)
		value = "";
	return (dup_or_error(value, minishell));
}

char	*parser_expand_variable(const char *word, size_t *i,
		t_minishell *minishell)
{
	char	*expanded;

	(*i)++;
	if (word[*i] == '?')
	{
		expanded = ft_itoa(minishell->exit_status);
		if (expanded == NULL)
			return (parser_expand_malloc_error(minishell), NULL);
		return ((*i)++, expanded);
	}
	if (word[*i] == '\0' || !is_var_char(word[*i]))
		return (dup_or_error("$", minishell));
	return (expand_named_variable(word, i, minishell));
}
