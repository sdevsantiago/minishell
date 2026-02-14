/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:10:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 16:10:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	command_clear_argv(
	t_command *command
)
{
	int	i;

	if (command->argv != NULL)
	{
		i = 0;
		while (i < command->argc)
		{
			free(command->argv[i]);
			i++;
		}
		free(command->argv);
		command->argv = NULL;
	}
}

void	command_clear(
	t_command *command
)
{
	if (command != NULL)
	{
		command_clear_argv(command);
		ft_lstclear(&command->redirections,
			(void (*)(void *))redirection_clear);
		ft_lstclear(&command->heredocs, (void (*)(void *))redirection_clear);
		free(command);
	}
}
