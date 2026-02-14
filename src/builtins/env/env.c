/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:05:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/09 22:05:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_entry(t_map_entry *entry);
static void	print_env(t_minishell *msh);

uint8_t	builtin_env(
	t_command cmd,
	t_minishell *msh
)
{
	if (cmd.argc > 1)
	{
		ft_eprintf("minishell: env: %s: No such file or directory\n",
			cmd.argv[1]);
		return (127);
	}
	print_env(msh);
	return (EXIT_SUCCESS);
}

static void	print_entry(
	t_map_entry *entry
)
{
	ft_putstr((char *)entry->key);
	ft_putchar('=');
	if (entry->value != NULL)
		ft_putstr((char *)entry->value);
	ft_putchar('\n');
}

static void	print_env(
	t_minishell *msh
)
{
	t_list	*entries;
	t_list	*current;

	entries = ft_hashmap_entries(msh->variables.environment);
	current = entries;
	while (current != NULL)
	{
		print_entry((t_map_entry *)current->content);
		current = current->next;
	}
	ft_lstclear_nodes(&entries);
}
