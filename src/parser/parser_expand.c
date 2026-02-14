/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:24:45 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 06:56:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand_internal.h"

static void	command_clear_argv_expand(
	t_command *command
)
{
	int	i;

	i = 0;
	while (i < command->argc)
	{
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
}

static bool	command_set_expanded_argv(
	t_command *command,
	t_list *expanded_args,
	t_minishell *minishell
)
{
	char	**argv;
	t_list	*current;
	int		argc;
	int		i;

	argc = ft_lstsize(expanded_args);
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
		return (ft_lstclear(&expanded_args, free),
			parser_expand_malloc_error(minishell), false);
	i = 0;
	current = expanded_args;
	while (current != NULL)
	{
		argv[i++] = (char *)current->content;
		current = current->next;
	}
	argv[i] = NULL;
	ft_lstclear_nodes(&expanded_args);
	command_clear_argv_expand(command);
	command->argc = argc;
	command->argv = argv;
	return (true);
}

static bool	expand_argv(
	t_command *command,
	t_minishell *minishell
)
{
	int		i;
	t_list	*expanded_args;
	t_list	*fields;
	t_list	*last;

	i = 0;
	expanded_args = NULL;
	while (i < command->argc)
	{
		fields = NULL;
		if (!parser_expand_word_fields(command->argv[i], minishell,
				true, &fields))
			return (ft_lstclear(&expanded_args, free), false);
		if (expanded_args == NULL)
			expanded_args = fields;
		else
		{
			last = ft_lstlast(expanded_args);
			if (last != NULL)
				last->next = fields;
		}
		i++;
	}
	return (command_set_expanded_argv(command, expanded_args, minishell));
}

static bool	expand_redirections(
	t_list *redirections,
	t_minishell *minishell
)
{
	t_redirection	*redirection;
	char			*expanded;

	while (redirections != NULL)
	{
		redirection = (t_redirection *)redirections->content;
		expanded = parser_expand_word(redirection->target, minishell,
				true);
		if (expanded == NULL)
			return (false);
		free(redirection->target);
		redirection->target = expanded;
		redirections = redirections->next;
	}
	return (true);
}

void	expand(
	t_list **commands,
	t_minishell *minishell
)
{
	t_list		*current;
	t_command	*command;

	if (commands == NULL || *commands == NULL)
		return ;
	current = *commands;
	while (current != NULL)
	{
		command = (t_command *)current->content;
		if (!expand_argv(command, minishell)
			|| !expand_redirections(command->redirections, minishell)
			|| !expand_redirections(command->heredocs, minishell))
		{
			ft_lstclear(commands, (void (*)(void *))command_clear);
			*commands = NULL;
			return ;
		}
		current = current->next;
	}
}
