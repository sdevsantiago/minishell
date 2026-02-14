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

uint8_t	builtin_pwd(
	t_command cmd,
	t_minishell *msh
){
	char	*cwd;

	(void)cmd;
	(void)msh;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell: pwd");
		return (EXIT_FAILURE);
	}
	ft_putendl(cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
