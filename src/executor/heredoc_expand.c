/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:30:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 17:30:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "variables.h"
#include "errors.h"

static bool	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static bool	append_text(char **result, const char *value)
{
	char	*joined;

	joined = ft_strnjoin(2, *result, (char *)value);
	if (joined == NULL)
	{
		free(*result);
		*result = NULL;
		return (false);
	}
	free(*result);
	*result = joined;
	return (true);
}

static char	*expand_variable(const char *line, size_t *i, t_minishell *msh)
{
	char	*name;
	char	*value;
	size_t	start;

	(*i)++;
	if (line[*i] == '?')
		return ((*i)++, ft_itoa(msh->exit_status));
	if (line[*i] == '\0' || !is_var_char(line[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (line[*i] != '\0' && is_var_char(line[*i]))
		(*i)++;
	name = ft_substr(line, start, *i - start);
	if (name == NULL)
		return (NULL);
	value = get_var(name, msh);
	free(name);
	if (value == NULL)
		value = "";
	return (ft_strdup(value));
}

static char	*expand_literal_char(const char *line, size_t *i,
		bool *in_single, bool *in_double)
{
	char	value[2];

	if (line[*i] == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (line[*i] == '\"' && !*in_single)
		*in_double = !*in_double;
	value[0] = line[*i];
	value[1] = '\0';
	(*i)++;
	return (ft_strdup(value));
}

char	*executor_expand_heredoc_line(
	const char *line,
	t_minishell *minishell
)
{
	char	*result;
	char	*expanded;
	size_t	i;
	bool	in_single;
	bool	in_double;

	result = ft_strdup("");
	if (result == NULL)
		return (malloc_error(), NULL);
	i = 0;
	in_single = false;
	in_double = false;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && !in_single)
			expanded = expand_variable(line, &i, minishell);
		else
			expanded = expand_literal_char(line, &i, &in_single, &in_double);
		if (expanded == NULL)
			return (free(result), malloc_error(), NULL);
		if (!append_text(&result, expanded))
			return (free(expanded), malloc_error(), NULL);
		free(expanded);
	}
	return (result);
}
