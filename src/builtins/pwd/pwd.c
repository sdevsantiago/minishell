/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 22:08:55 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/01 16:27:08 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

u_int8_t	builtin_pwd(
	t_command cmd,
	t_minishell *msh
){
	char	cwd[PATH_MAX];

	(void)cmd;
	(void)msh;
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_putendl(cwd);
	return (EXIT_SUCCESS);
}
