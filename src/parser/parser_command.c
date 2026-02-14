/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:26:42 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/13 21:26:42 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_list	*ft_lstfind(t_list *lst, bool (*pre)(void *));

/**
 * @brief Creates a new command from a list of tokens.
 *
 * @param tokens The list of tokens to create the command from.
 *
 * @return A new command or NULL on error.
 *
 * @note The `tokens` pointer is moved to the next command's tokens.
 */
t_command	*command_new(
	t_list **tokens
)
{
	t_command	*command;
	t_list		*current_token;
	t_list		*delimiter_token;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (command == NULL)
		return (NULL);
	current_token = *tokens;
	delimiter_token = ft_lstfind(current_token, (bool (*)(void *))is_pipe);
	while (command != NULL && current_token != delimiter_token)
		command_add_tokens(&command, &current_token);
	*tokens = current_token;
	return (command);
}

/**
 * @brief Adds a token to a command, updating the command's arguments and
 *        redirections as necessary.
 *
 * @param command The command to add the token to.
 * @param tokens  The list of tokens to add to the command.
 *
 * @note The `command` pointer can be free'd if there is an error while adding
 *       the token.
 */
void	command_add_tokens(
	t_command **command,
	t_list **tokens
)
{
	t_token	*token;
	int		io_number;

	token = (t_token *)(*tokens)->content;
	if (parser_token_is_fd_prefix(*tokens, &io_number))
	{
		*tokens = (*tokens)->next;
		token = (t_token *)(*tokens)->content;
		redirection_add_with_fd(tokens, token, command, io_number);
		return ;
	}
	if (is_redirection(token))
		redirection_add_with_fd(tokens, token, command, -1);
	else
		words_add(tokens, command);
}

/**
 * @brief Checks if a token is a redirection token.
 *
 * @param token The token to check.
 *
 * @return `true` if the token is a redirection token, `false` otherwise.
 */
bool	is_redirection(
	t_token *token
)
{
	return (token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC);
}

/**
 * @brief Checks if a token is a pipe token.
 *
 * @param token The token to check.
 *
 * @return `true` if the token is a pipe token, `false` otherwise.
 */
bool	is_pipe(
	t_token *token
)
{
	return (token->type == TOKEN_PIPE);
}

/**
 * @brief Finds a node in a linked list that satisfies a given predicate.
 *
 * @param lst The linked list to search through.
 * @param pre   The predicate function to apply to each node's content.
 *
 * @returns The first node that satisfies the predicate or `NULL` if no such
 *          node exists or if the list is `NULL`.
 */
static t_list	*ft_lstfind(
	t_list *lst,
	bool (*pre)(void *))
{
	while (lst != NULL)
	{
		if (pre(lst->content))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
