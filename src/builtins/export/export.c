/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:05:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/14 02:02:14 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static uint8_t	export_one(char *arg, t_minishell *msh);
static uint8_t	print_exported(t_minishell *msh);
static void		**entries_to_array(t_list *lst, size_t *count,
					bool add_oldpwd, t_map_entry *oldpwd_entry);
static bool		print_sorted_entries(t_map_entry **entries, size_t count);
bool			export_is_valid_identifier(const char *arg, size_t name_len);
void			export_parse_assignment(char *arg, char **eq_pos,
					size_t *name_len, bool *append);
uint8_t			export_set_assigned_value(const char *name, char *eq_pos,
					bool append, t_minishell *msh);
bool			export_print_declaration(const char *name, const char *value);
void			export_sort_entries(t_map_entry **entries, size_t count);

uint8_t	builtin_export(
	t_command cmd,
	t_minishell *msh
)
{
	uint8_t	status;
	uint8_t	result;
	size_t	i;

	if (cmd.argc == 1)
		return (print_exported(msh));
	status = EXIT_SUCCESS;
	i = 0;
	while (cmd.argv[++i] != NULL)
	{
		result = export_one(cmd.argv[i], msh);
		if (result == 2)
			return (2);
		if (result != EXIT_SUCCESS)
			status = EXIT_FAILURE;
	}
	return (status);
}

static uint8_t	export_one(
	char *arg,
	t_minishell *msh
)
{
	char	*eq_pos;
	char	*name;
	size_t	name_len;
	bool	append;

	if (arg[0] == '-' && arg[1] != '\0')
		return (ft_eprintf("minishell: export: %s: invalid option\n", arg),
			ft_eputendl("export: usage: export [name[=value] ...]"), 2);
	export_parse_assignment(arg, &eq_pos, &name_len, &append);
	if (!export_is_valid_identifier(arg, name_len))
		return (ft_eprintf(
				"minishell: export: `%s': not a valid identifier\n", arg),
			EXIT_FAILURE);
	name = ft_substr(arg, 0, name_len);
	if (name == NULL)
		return (EXIT_FAILURE);
	if (export_set_assigned_value(name, eq_pos, append, msh) != EXIT_SUCCESS)
		return (free(name), EXIT_FAILURE);
	free(name);
	return (EXIT_SUCCESS);
}

static uint8_t	print_exported(
	t_minishell *msh
)
{
	t_list		*entries;
	t_map_entry	**sorted_entries;
	t_map_entry	oldpwd_entry;
	size_t		count;

	entries = ft_hashmap_entries(msh->variables.environment);
	if (entries == NULL)
		return (EXIT_SUCCESS);
	oldpwd_entry = (t_map_entry){"OLDPWD", NULL};
	sorted_entries = (t_map_entry **)entries_to_array(entries, &count,
			!ft_hashmap_contains_key(msh->variables.environment, "OLDPWD"),
			&oldpwd_entry);
	ft_lstclear_nodes(&entries);
	if (sorted_entries == NULL)
		return (EXIT_FAILURE);
	export_sort_entries(sorted_entries, count);
	if (!print_sorted_entries(sorted_entries, count))
		return (free(sorted_entries), EXIT_FAILURE);
	return (free(sorted_entries), EXIT_SUCCESS);
}

static void	**entries_to_array(
	t_list *entries,
	size_t *count,
	bool add_oldpwd,
	t_map_entry *oldpwd_entry
)
{
	void		**array;
	t_list		*node;
	t_map_entry	*entry;
	size_t		i;

	*count = (size_t)ft_lstsize(entries) + (size_t)add_oldpwd;
	array = (void **)malloc(sizeof(void *) * (*count));
	if (array == NULL)
		return (NULL);
	i = 0;
	node = entries;
	while (node != NULL)
	{
		entry = (t_map_entry *)node->content;
		if (entry != NULL && ft_strcmp((char *)entry->key, "_") != 0)
			array[i++] = entry;
		node = node->next;
	}
	if (add_oldpwd)
		array[i++] = oldpwd_entry;
	*count = i;
	return (array);
}

static bool	print_sorted_entries(
	t_map_entry **entries,
	size_t count
)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!export_print_declaration((char *)entries[i]->key,
				(char *)entries[i]->value))
			return (false);
		i++;
	}
	return (true);
}
