/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:28:35 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/13 21:28:35 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "errors.h"

static t_redirection	*redirection_new(t_list **tokens, int io_number);
static bool				redirection_read_target(t_redirection *rd, t_list **tk);
static bool				has_single_quote(const char *value);

/**
 * @brief Creates a new redirection from a list of tokens.
 *
 * @param tokens The list of tokens to create the redirection from.
 *
 * @return A new redirection or `NULL` on error.
 */
static t_redirection	*redirection_new(
	t_list **tokens,
	int io_number
)
{
	t_redirection	*redirection;
	t_token			*token;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (redirection == NULL)
		return (malloc_error(), NULL);
	token = (t_token *)(*tokens)->content;
	redirection->type = token->type;
	redirection->heredoc_expand = true;
	redirection->heredoc_ready = false;
	if (io_number < 0)
		redirection->io_number = STDOUT_FILENO;
	else
		redirection->io_number = io_number;
	if (io_number < 0 && (token->type == TOKEN_REDIRECT_IN
			|| token->type == TOKEN_HEREDOC))
		redirection->io_number = STDIN_FILENO;
	if (!redirection_read_target(redirection, tokens))
		return (free(redirection), NULL);
	return (redirection);
}

static bool	redirection_read_target(
	t_redirection *rd,
	t_list **tk
)
{
	t_token	*token;

	*tk = (*tk)->next;
	if (*tk == NULL)
		return (syntax_error_unexpected_token(NULL), false);
	token = (t_token *)(*tk)->content;
	if (token->type != TOKEN_WORD)
	{
		while (*tk != NULL)
			*tk = (*tk)->next;
		return (syntax_error_unexpected_token(token), false);
	}
	if (rd->type == TOKEN_HEREDOC && has_single_quote(token->value))
		rd->heredoc_expand = false;
	rd->target = ft_strdup(token->value);
	if (rd->target == NULL)
		return (malloc_error(), false);
	*tk = (*tk)->next;
	return (true);
}

static bool	has_single_quote(
	const char *value
)
{
	size_t	i;

	if (value == NULL)
		return (false);
	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

void	redirection_clear(
	t_redirection *redirection
)
{
	if (redirection != NULL)
	{
		free(redirection->target);
		free(redirection);
	}
}

void	redirection_add_with_fd(
	t_list **tokens,
	t_token *token,
	t_command **command,
	int io_number
)
{
	t_redirection	*redirection;
	t_list			*redirection_tokens;

	redirection = redirection_new(tokens, io_number);
	if (redirection == NULL)
	{
		command_clear(*command);
		*command = NULL;
		return ;
	}
	redirection_tokens = ft_lstnew(redirection);
	if (redirection_tokens == NULL)
	{
		free(redirection);
		return (malloc_error());
	}
	(void)token;
	ft_lstadd_back(&(*command)->redirections, redirection_tokens);
}
