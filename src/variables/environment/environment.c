/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:12:39 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/01 13:01:56 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses and stores environment variables from envp array into a hashmap
 *
 * This function iterates through the environment variables array (envp) and
 * splits each variable string on the '=' delimiter to separate the variable
 * name from its value. Each name-value pair is then stored in the minishell's
 * environment hashmap for later retrieval.
 *
 * @param envp Array of environment variable strings in "NAME=value" format
 * @param msh  Pointer to the minishell structure containing the environment
 *             hashmap
 *
 * @note The function assumes envp strings are in the standard format
 *       "NAME=value"
 */
void	set_envp(
	char **envp,
	t_minishell *msh
) {
	char	**splitted_env;

	if (msh == NULL)
	{
		ft_hashmap_clear(&msh->variables.environment, free);
		return ;
	}
	while (*envp != NULL)
	{
		splitted_env = ft_split(*envp, '=');
		if (splitted_env == NULL)
		{
			ft_hashmap_clear(&msh->variables.environment, free);
			return ;
		}
		ft_hashmap_put(msh->variables.environment,
			ft_strdup(splitted_env[0]), ft_strdup(splitted_env[1]));
		ft_free_split(splitted_env);
		envp++;
	}
}

/**
 * @brief Sets an environment variable in the minishell's environment hashmap.
 *
 * This function adds a new environment variable or updates an existing one
 * in the minishell's environment hashmap. If the variable already exists,
 * the old value is freed to prevent memory leaks. If the variable is new,
 * a duplicate of the key name is created for storage.
 *
 * @param env_name  The name of the environment variable to set
 * @param env_value The value to assign to the environment variable
 * @param msh       Pointer to the minishell structure containing the
 *                  environment hashmap
 */
void	set_env(
	const char *env_name,
	char *env_value,
	t_minishell *msh
) {
	t_hashmap	*environment;
	const char	*key;
	char		*old_value;

	environment = msh->variables.environment;
	key = env_name;
	if (!ft_hashmap_contains_key(environment, key))
		key = ft_strdup(env_name);
	old_value = ft_hashmap_put(environment, key, ft_strdup(env_value));
	if (old_value != NULL)
		free(old_value);
}

/**
 * @brief Converts the environment variables hashmap to an envp array format.
 *
 * This function extracts all environment variables from the minishell's
 * environment hashmap and converts them into a NULL-terminated array of
 * strings in the format "KEY=VALUE".
 *
 * @param msh Pointer to the minishell structure containing the environment
 *            variables hashmap.
 *
 * @return A dynamically allocated array of strings representing environment
 *         variables in "KEY=VALUE" format, terminated by NULL. Returns NULL
 *         if memory allocation fails. The caller is responsible for freeing
 *         the returned array and its individual string elements using
 *         the `free_envp()` function.
 *
 * @note The function allocates memory for both the array and individual
 *       strings using malloc and ft_strnjoin respectively.
 * @note The returned array size is environment->size + 1 to accommodate
 *       the NULL terminator.
 */
char	**get_envp(
	t_minishell *msh
) {
	char		**envp;
	t_list		*env_list;
	t_list		*env;
	t_map_entry	*entry;
	size_t		i;

	env_list = ft_hashmap_entries(msh->variables.environment);
	envp = (char **)malloc(
		(msh->variables.environment->size + 1) * sizeof(char *));
	if (envp != NULL)
	{
		i = 0;
		env = env_list;
		while (env != NULL)
		{
			entry = env->content;
			envp[i++] = ft_strnjoin(3, entry->key, "=", entry->value);
			env = env->next;
		}
		envp[i] = NULL;
	}
	ft_lstclear_nodes(&env_list);
	return (envp);
}

/**
 * @brief Frees a dynamically allocated environment variables array
 *
 * This function deallocates memory for an array of strings that was previously
 * allocated by `get_envp()`. It iterates through each string in the array,
 * frees the memory for individual strings, and then frees the array itself.
 *
 * @param envp Pointer to the array of environment variable strings to be freed.
 *             Each string in the array should be dynamically allocated.
 *             The array must be NULL-terminated.
 */
void	free_envp(
	char **envp
) {
	size_t	i;

	i = -1;
	while (envp[++i] != NULL)
		free(envp[i]);
	free(envp);
}

/**
 * @brief Retrieves the value of an environment variable from the shell's
 *        environment hashmap.
 *
 * This function searches for the specified environment variable name in the
 * minishell's environment variable hashmap and returns its associated value.
 *
 * @param env_name The name of the environment variable to retrieve (e.g.,
 *                 "PATH", "HOME")
 * @param msh      Pointer to the minishell structure containing the environment
 *                 variables hashmap
 *
 * @return The value of the environment variable if found, NULL if not found
 */
char	*get_env(
	const char *env_name,
	t_minishell *msh
) {
	return (ft_hashmap_get(msh->variables.environment, env_name));
}
