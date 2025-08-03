/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:15:09 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/03 02:33:30 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	printenv(char **envp);

int	env_builtin(
	int argc,
	char const *argv[])
{
	(void)argc;
	(void)argv;
	// if (!argv || !*argv)
		// printenv(envp);
	return (0);
}

// static void	printenv(
// 	char **envp)
// {
// 	size_t	i;

// 	i = 0;
// 	while (envp[i])
// 		ft_putendl(envp[i++]);
// }
