/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:38 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/13 21:22:06 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "errors.h"

static t_list	*parse_tokens(t_list *tokens);
static bool		parse_add_command(t_list **commands, t_list **current_token);
static bool		parse_advance_token(t_list **commands, t_list **current_token);

/**
 * @brief Converts a command line string into a list of commands.
 *
 * @param line      The command line string to parse.
 * @param minishell The minishell instance.
 *
 * @return A list of commands or `NULL` on error.
 */
t_list	*parse(
	char *line,
	t_minishell *minishell
)
{
	t_list	*commands;
	t_list	*tokens;

	if (line == NULL)
		return (NULL);
	tokens = lex(line);
	commands = parse_tokens(tokens);
	ft_lstclear(&tokens, (void (*)(void *))token_clear);
	expand(&commands, minishell);
	return (commands);
}

/**
 * @brief Converts a list of tokens into a list of commands.
 *
 * @param tokens    The list of tokens to parse.
 *
 * @return A list of commands or `NULL` on error.
 */
static t_list	*parse_tokens(
	t_list *tokens
)
{
	t_list	*commands;
	t_list	*current_token;

	if (tokens == NULL)
		return (NULL);
	commands = NULL;
	current_token = tokens;
	if (((t_token *)current_token->content)->type == TOKEN_PIPE)
		return (syntax_error_unexpected_token(
				(t_token *)current_token->content), NULL);
	while (current_token != NULL && parse_add_command(&commands, &current_token)
		&& parse_advance_token(&commands, &current_token))
		continue ;
	if (current_token != NULL)
		return (NULL);
	return (commands);
}

static bool	parse_add_command(
	t_list **commands,
	t_list **current_token
)
{
	t_command	*command;
	t_list		*new_command;

	command = command_new(current_token);
	if (command == NULL)
		return (ft_lstclear(commands, (void (*)(void *))command_clear), false);
	new_command = ft_lstnew(command);
	if (new_command == NULL)
	{
		command_clear(command);
		return (ft_lstclear(commands, (void (*)(void *))command_clear),
			malloc_error(), false);
	}
	ft_lstadd_back(commands, new_command);
	return (true);
}

static bool	parse_advance_token(
	t_list **commands,
	t_list **current_token
)
{
	if (*current_token == NULL)
		return (true);
	if ((*current_token)->next == NULL)
	{
		ft_lstclear(commands, (void (*)(void *))command_clear);
		return (syntax_error_unexpected_token(
				(t_token *)(*current_token)->content), false);
	}
	*current_token = (*current_token)->next;
	return (true);
}
