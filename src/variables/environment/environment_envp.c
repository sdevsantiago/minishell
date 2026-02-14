/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:10:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 16:10:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"
#include "variables.h"
#include "errors.h"

static void	fill_envp(
	char **envp,
	t_list *env_list
)
{
	t_list		*env;
	t_map_entry	*entry;
	size_t		i;

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

char	**get_envp(
	t_minishell *minishell
)
{
	char	**envp;
	t_list	*env_list;

	env_list = ft_hashmap_entries(minishell->variables.environment);
	envp = (char **)malloc(
			(minishell->variables.environment->size + 1) * sizeof(char *)
			);
	if (envp != NULL)
		fill_envp(envp, env_list);
	ft_lstclear_nodes(&env_list);
	return (envp);
}

static bool	import_env_entry(
	char *entry_text,
	t_minishell *minishell
)
{
	char	*equal;
	char	*key;
	char	*value;
	size_t	key_len;

	equal = ft_strchr(entry_text, '=');
	if (equal == NULL)
		return (true);
	key_len = (size_t)(equal - entry_text);
	key = ft_substr(entry_text, 0, key_len);
	value = ft_strdup(equal + 1);
	if (key == NULL || value == NULL)
		return (free(key), free(value), minishell->exit = true,
			malloc_error(), false);
	set_env(key, value, minishell);
	free(key);
	free(value);
	return (!minishell->exit);
}

static void	update_shlvl(
	t_minishell *minishell
)
{
	char	*value;
	char	*new_shlvl;
	int		shlvl;

	value = get_env("SHLVL", minishell);
	shlvl = 0;
	if (value != NULL)
		shlvl = ft_atoi(value);
	if (shlvl < 0)
		shlvl = 0;
	new_shlvl = ft_itoa(shlvl + 1);
	if (new_shlvl == NULL)
		return ((void)(minishell->exit = true), malloc_error());
	set_env("SHLVL", new_shlvl, minishell);
	free(new_shlvl);
}

void	set_envp(
	char **envp,
	t_minishell *minishell
)
{
	t_hashmap	*environment;

	if (minishell == NULL || envp == NULL)
		return ;
	environment = ft_hashmap_new(32, ft_hashmap_hashstr, ft_hashmap_strcmp);
	if (environment == NULL)
		return ;
	minishell->variables.environment = environment;
	while (*envp != NULL)
	{
		if (!import_env_entry(*envp, minishell))
			return ;
		envp++;
	}
	update_shlvl(minishell);
}
