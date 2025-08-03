/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:52:33 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/03 02:11:02 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd_builtin(
	int argc,
	char const *argv[])
{
	char cwd[PATH_MAX];

	(void)argc;
	(void)argv;
	if (!getcwd(cwd, sizeof(cwd)))
		ft_eputendl("getcwd()");
	ft_putendl(cwd);
	return (0);
}
