/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:20:48 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/08 21:16:18 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	exit_arg_is_invalid(const char *arg)
{
	if (arg == NULL)
		return (true);
	if (arg[0] == '\0')
		return (true);
	if ((*arg == '+' || *arg == '-') && arg[1] == '\0')
		return (true);
	if (!ft_strisnum(arg))
		return (true);
	return (false);
}

uint8_t	builtin_exit(
	t_command cmd,
	t_minishell *msh
)
{
	if (isatty(STDIN_FILENO))
		ft_eputendl("exit");
	if (cmd.argc == 1)
	{
		msh->exit = 1;
		return (msh->exit_status);
	}
	if (exit_arg_is_invalid(cmd.argv[1]))
	{
		ft_eprintf("minishell: exit: %s: numeric argument required\n",
			cmd.argv[1]);
		msh->exit = 1;
		msh->exit_status = 2;
		return (msh->exit_status);
	}
	if (cmd.argc > 2)
	{
		ft_eputendl("minishell: exit: too many arguments");
		msh->exit_status = EXIT_FAILURE;
		return (msh->exit_status);
	}
	msh->exit = 1;
	msh->exit_status = (uint8_t)ft_atol(cmd.argv[1]);
	return (msh->exit_status);
}
