/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:29:43 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 15:17:17 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"
#include "errors.h"

/**
 * @brief Retrieves the value of an internal variable by name.
 * 
 * @param name      The name of the internal variable to retrieve.
 * @param minishell Pointer to the minishell structure.
 * 
 * @return The value of the internal variable if found, or NULL if not found.
 */
char	*get_int(
	const char *name,
	t_minishell *minishell
)
{
	return (ft_hashmap_get(minishell->variables.internal, name));
}

/**
 * @brief Stores a variable as internal.
 * 
 * @param name      The name of the internal variable to set.
 * @param value     The value to associate with the internal variable.
 * @param minishell Pointer to the minishell structure.
 * 
 * @note If the internal variable already exists, its value will be updated and
 *       the old value will be freed. If it does not exist, a new internal
 *       variable will be created.
 */
void	set_int(
	const char *name,
	char *value,
	t_minishell *minishell
)
{
	t_hashmap		*internal;
	char			*key;
	char			*val;
	char			*old_val;

	internal = minishell->variables.internal;
	key = (char *)name;
	if (key != NULL && !ft_hashmap_contains_key(internal, key))
	{
		key = ft_strdup(name);
		if (key == NULL)
			return (minishell->exit = true, malloc_error());
	}
	val = value;
	if (val != NULL)
		val = ft_strdup(value);
	if (val == NULL)
	{
		if (key != name)
			free(key);
		return (minishell->exit = true, malloc_error());
	}
	old_val = ft_hashmap_put(internal, key, val);
	if (old_val != NULL)
		free(old_val);
}

/**
 * @brief Removes an internal variable by name.
 * 
 * @param name      The name of the internal variable to remove.
 * @param minishell Pointer to the minishell structure.
 * 
 * @note If the internal variable exists, it will be removed from the hashmap
 *       and its associated value will be freed.
 */
void	unset_int(
	const char *name,
	t_minishell *minishell
)
{
	char	*value;

	value = ft_hashmap_remove(minishell->variables.internal, (void *)name);
	if (value != NULL)
		free(value);
}

/**
 * @brief Initializes the internal variables hashmap with default values.
 * 
 * @param minishell Pointer to the minishell structure to initialize.
 *
 * @warning This function must be called only once during the initialization of
 *          the minishell. 
 */
void	set_intp(
	t_minishell *minishell
)
{
	if (minishell == NULL)
		return ;
	minishell->variables.internal
		= ft_hashmap_new(16, ft_hashmap_hashstr, ft_hashmap_strcmp);
	if (minishell->variables.internal == NULL)
		return ;
	set_int("?", "0", minishell);
	set_int("_", "minishell", minishell);
	set_int("PS0", "", minishell);
	set_int("PS1", DEFAULT_PS1, minishell);
	set_int("PS2", DEFAULT_PS2, minishell);
	set_int("MINISHELL", "minishell", minishell);
	set_int("MINISHELL_VERSION", MINISHELL_VERSION, minishell);
}
