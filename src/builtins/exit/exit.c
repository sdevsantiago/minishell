/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:20:48 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/30 09:08:02 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

u_int8_t	builtin_exit(
	t_command cmd,
	t_minishell *msh
){
	ft_eputendl("exit");
	if (cmd.argc == 1)
	{
		// msh.exit = 1;
		// return the last exit_status, if none 0 is returned
		return (msh->exit_status);
	}
	else if (!ft_strisnum(cmd.argv[1]))
	{
		ft_eputstr("exit: ");
		ft_eputendl(cmd.argv[1]);
		ft_eputendl(": numeric argument required");
		return (2);
	}
	else if (cmd.argc > 2)
	{
		ft_eputendl("exit: too many arguments");
		return (2);
	}
	else
	{
		// msh.exit = 1;
		// cast to u_int8_t causes to return a value between 0 and 255
		return ((u_int8_t)ft_atol(cmd.argv[1]));
	}
}
