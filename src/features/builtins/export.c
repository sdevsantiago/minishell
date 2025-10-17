/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:38:45 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/05 14:55:31 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_builtin(int argc, char const *argv[], char **envp)
{
	size_t	i;
	char	**env;

	(void)argv;
	if (argc == 2)
	{
		i = 0;
		env = ft_split(argv[1], '=');
		while (envp[i]) // ENV=value
		{
			if (ft_strncmp(envp[i], env[0], ft_strlen(env[0])) == 0)
			{
				char *line = ft_strnjoin(3, env[0], "=", env[1]);
				envp[i] = line;
				break ;
			}
			i++;
		}
		ft_free_split(env);
	}
	return (0);
}
