/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:00:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/13 00:00:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	cmdfree_argv(
	char **argv
)
{
	size_t	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static void	cmdfree_redirection(
	t_redirection *redirection
)
{
	if (redirection == NULL)
		return ;
	if (redirection->type == TOKEN_HEREDOC && redirection->heredoc_ready
		&& redirection->target != NULL)
		unlink(redirection->target);
	free(redirection->target);
	free(redirection);
}

void	executor_cmdfree(
	t_command *command
)
{
	if (command == NULL)
		return ;
	cmdfree_argv(command->argv);
	free(command->path);
	ft_lstclear(&command->redirections,
		(void (*)(void *))cmdfree_redirection);
	ft_lstclear(&command->heredocs, (void (*)(void *))cmdfree_redirection);
	free(command);
}
