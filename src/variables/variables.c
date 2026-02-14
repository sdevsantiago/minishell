/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:41:44 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 00:52:12 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

/**
 * @brief Retrieves the value of a variable by name.
 * 
 * @param name      The name of the variable to retrieve.
 * @param minishell Pointer to the minishell structure.
 * 
 * @return The value of the variable if found, or NULL if not found.
 */
char	*get_var(
	const char *name,
	t_minishell *minishell
)
{
	char	*value;

	value = get_int(name, minishell);
	if (value == NULL)
		value = get_env(name, minishell);
	return (value);
}

void	set_var(const char *name, char *value, t_minishell *minishell)
{
	if (ft_hashmap_contains_key(minishell->variables.internal, name))
		set_int(name, value, minishell);
	set_env(name, value, minishell);
}

void	unset_var(
	const char *name,
	t_minishell *minishell
)
{
	unset_int(name, minishell);
	unset_env(name, minishell);
}
