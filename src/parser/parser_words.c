/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:29:44 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 03:34:38 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	args_add_word(
	t_list **args,
	const char *value
)
{
	t_list	*node;
	char	*dup;

	dup = ft_strdup(value);
	if (dup == NULL)
		return (false);
	node = ft_lstnew(dup);
	if (node == NULL)
		return (free(dup), false);
	ft_lstadd_back(args, node);
	return (true);
}

static bool	words_collect(
	t_list *arg,
	t_list **args,
	int *new_argc,
	t_list **end
)
{
	t_token	*token;
	int		io_number;

	while (arg != NULL)
	{
		token = (t_token *)arg->content;
		if (token->type != TOKEN_WORD || parser_token_is_fd_prefix(arg,
				&io_number))
			break ;
		if (!args_add_word(args, token->value))
			return (false);
		(*new_argc)++;
		arg = arg->next;
	}
	*end = arg;
	return (true);
}

static bool	command_append_words(
	t_command *command,
	t_list **args,
	int new_argc
)
{
	char	**argv;
	t_list	*current;
	int		i;

	argv = (char **)malloc(sizeof(char *) * (command->argc + new_argc + 1));
	if (argv == NULL)
		return (false);
	i = 0;
	while (i < command->argc)
	{
		argv[i] = command->argv[i];
		i++;
	}
	current = *args;
	while (current != NULL)
	{
		argv[i++] = (char *)current->content;
		current = current->next;
	}
	argv[i] = NULL;
	free(command->argv);
	ft_lstclear_nodes(args);
	command->argv = argv;
	command->argc += new_argc;
	return (true);
}

/**
 * @brief Adds all consecutive word tokens to a command's argv and updates its
 *        argc accordingly.
 *
 * @param command The command to add the word tokens to.
 * @param tokens  The list of tokens to add to the command.
 */
void	words_add(
	t_list **tokens,
	t_command **command
)
{
	t_list	*args;
	int		new_argc;

	args = NULL;
	new_argc = 0;
	if (!words_collect(*tokens, &args, &new_argc, tokens)
		|| !command_append_words(*command, &args, new_argc))
		return (ft_lstclear(&args, free), command_clear(*command),
			*command = NULL, (void)0);
}
