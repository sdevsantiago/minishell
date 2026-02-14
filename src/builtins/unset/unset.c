/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:05:00 by codex             #+#    #+#             */
/*   Updated: 2026/02/09 22:05:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static uint8_t	is_valid_identifier(const char *arg);
static uint8_t	unset_one(char *arg, t_minishell *msh);
static bool		is_option(const char *arg);

uint8_t	builtin_unset(
	t_command cmd,
	t_minishell *msh
)
{
	uint8_t	status;
	uint8_t	result;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 0;
	while (cmd.argv[++i] != NULL)
	{
		result = unset_one(cmd.argv[i], msh);
		if (result == 2)
			return (2);
		if (result != EXIT_SUCCESS)
			status = EXIT_FAILURE;
	}
	return (status);
}

static uint8_t	is_valid_identifier(
	const char *arg
)
{
	size_t	i;

	if (arg == NULL || *arg == '\0')
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 0;
	while (arg[++i] != '\0')
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
	return (1);
}

static uint8_t	unset_one(
	char *arg,
	t_minishell *msh
)
{
	if (is_option(arg))
	{
		ft_eprintf("minishell: unset: %s: invalid option\n", arg);
		ft_eputendl("unset: usage: unset [name ...]");
		return (2);
	}
	if (!is_valid_identifier(arg))
		return (EXIT_SUCCESS);
	unset_env(arg, msh);
	return (EXIT_SUCCESS);
}

static bool	is_option(
	const char *arg
)
{
	return (arg != NULL && arg[0] == '-' && arg[1] != '\0');
}
