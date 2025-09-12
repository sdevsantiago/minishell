/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:45:36 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/05 20:19:10 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	printenv_builtin(
	int argc,
	char const *argv[],
	char const *envp[])
{
	size_t	i;

	(void)argc;
	(void)argv;
	i = 0;
	while (envp[i])
		ft_putendl((char *)(envp[i++]));
	return (0);
}
