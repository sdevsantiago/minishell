/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:12:39 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 13:30:34 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"
#include "variables.h"
#include "errors.h"

static char	*resolve_key(
				const char *name,
				t_hashmap *environment,
				t_minishell *minishell,
				bool *owns_key
				);
static char	*resolve_value(
				char *value,
				t_minishell *minishell
				);

/**
 * @brief Retrieves the value of an environment variable from the shell's
 *        environment hashmap.
 *
 * This function searches for the specified environment variable name in the
 * minishell's environment variable hashmap and returns its associated value.
 *
 * @param name      The name of the environment variable to retrieve.
 * @param minishell Pointer to the minishell object.
 *
 * @return The value of the environment variable if found, NULL if not found
 */
char	*get_env(
	const char *name,
	t_minishell *minishell
)
{
	return (ft_hashmap_get(minishell->variables.environment, name));
}

/**
 * @brief Sets an environment variable in the minishell's environment hashmap.
 *
 * This function adds a new environment variable or updates an existing one
 * in the minishell's environment hashmap. If the variable already exists,
 * the old value is freed to prevent memory leaks. If the variable is new,
 * a duplicate of the key name is created for storage.
 *
 * @param name      The name of the environment variable to set
 * @param value     The value to assign to the environment variable
 * @param minishell Pointer to the minishell object.
 */
void	set_env(
	const char *name,
	char *value,
	t_minishell *minishell
)
{
	t_hashmap	*environment;
	char		*key;
	char		*val;
	char		*old_value;
	bool		owns_key;

	environment = minishell->variables.environment;
	key = resolve_key(name, environment, minishell, &owns_key);
	if (key == NULL)
		return ;
	val = resolve_value(value, minishell);
	if (val == NULL)
	{
		if (owns_key)
			free(key);
		return ;
	}
	old_value = ft_hashmap_put(environment, key, val);
	if (old_value != NULL)
		free(old_value);
}

/**
 * @brief Removes an environment variable by name.
 * 
 * @param name      The name of the environment variable to remove.
 * @param minishell Pointer to the minishell structure.
 * 
 * @note If the environment variable exists, it will be removed from the hashmap
 *       and its associated value will be freed.
 */
void	unset_env(
	const char *name,
	t_minishell *minishell
)
{
	t_hashmap	*environment;
	char		*val;

	environment = minishell->variables.environment;
	val = ft_hashmap_remove(environment, (void *)name);
	if (val != NULL)
		free(val);
}

static char	*resolve_key(
	const char *name,
	t_hashmap *environment,
	t_minishell *minishell,
	bool *owns_key
)
{
	char	*key;

	key = (char *)name;
	*owns_key = false;
	if (name == NULL)
		return (NULL);
	if (!ft_hashmap_contains_key(environment, name))
	{
		key = ft_strdup(name);
		if (key == NULL)
			return (minishell->exit = true, malloc_error(), NULL);
		*owns_key = true;
	}
	return (key);
}

static char	*resolve_value(
	char *value,
	t_minishell *minishell
)
{
	char	*val;

	if (value == NULL)
		val = ft_strdup("");
	else
		val = ft_strdup(value);
	if (val == NULL)
		return (minishell->exit = true, malloc_error(), NULL);
	return (val);
}
