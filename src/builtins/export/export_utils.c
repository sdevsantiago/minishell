/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:20:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 15:20:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	export_is_valid_identifier(
	const char *arg,
	size_t name_len
)
{
	size_t	i;

	if (name_len == 0 || arg == NULL)
		return (false);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	i = 0;
	while (++i < name_len)
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
	return (true);
}

void	export_parse_assignment(
	char *arg,
	char **eq_pos,
	size_t *name_len,
	bool *append
)
{
	char	*plus_eq;

	*append = false;
	*eq_pos = ft_strchr(arg, '=');
	*name_len = ft_strlen(arg);
	plus_eq = ft_strnstr(arg, "+=", *name_len);
	if (plus_eq != NULL)
	{
		*append = true;
		*name_len = (size_t)(plus_eq - arg);
		*eq_pos = plus_eq + 1;
	}
	else if (*eq_pos != NULL)
		*name_len = (size_t)(*eq_pos - arg);
}

uint8_t	export_set_assigned_value(
	const char *name,
	char *eq_pos,
	bool append,
	t_minishell *msh
)
{
	char	*current;
	char	*joined;

	if (append)
	{
		current = get_var((char *)name, msh);
		if (current == NULL)
			current = "";
		joined = ft_strnjoin(2, current, eq_pos + 1);
		if (joined == NULL)
			return (EXIT_FAILURE);
		set_var(name, joined, msh);
		free(joined);
		return (EXIT_SUCCESS);
	}
	if (eq_pos != NULL)
		set_var(name, eq_pos + 1, msh);
	else
		set_var(name, "", msh);
	return (EXIT_SUCCESS);
}

char	*export_escape_value(
	const char *value
)
{
	char	*escaped;
	size_t	i;
	size_t	j;

	escaped = (char *)malloc((ft_strlen(value) * 2) + 1);
	if (escaped == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '\\' || value[i] == '\"' || value[i] == '$')
			escaped[j++] = '\\';
		escaped[j++] = value[i++];
	}
	escaped[j] = '\0';
	return (escaped);
}

bool	export_print_declaration(
	const char *name,
	const char *value
)
{
	char	*escaped;

	ft_putstr("declare -x ");
	ft_putstr((char *)name);
	if (value != NULL)
	{
		escaped = export_escape_value(value);
		if (escaped == NULL)
			return (false);
		ft_putstr("=\"");
		ft_putstr(escaped);
		ft_putstr("\"");
		free(escaped);
	}
	ft_putchar('\n');
	return (true);
}
