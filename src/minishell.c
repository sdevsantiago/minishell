/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:51:33 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/01 13:38:35 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_init(
	t_minishell	*minishell,
	char		**envp
){
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->variables.environment
		= ft_hashmap_new(32, ft_hashmap_hashstr, ft_hashmap_strcmp);
	set_envp(envp, minishell);
	if (minishell->variables.environment == NULL)
		return (0);
	return (1);
}

u_int8_t	minishell_run(
	t_minishell	*minishell
){
	char		*line;
	t_command	command;

	line = NULL;
	while (!minishell->exit)
	{
		line = readline("minishell > ");
		if (*line)
		{
			add_history(line);
			command = parse(line, minishell);
			execute(command, minishell);
		}
		ft_free((void **)&line);
	}
	return (minishell->exit_status);
}

void	minishell_clear(
	t_minishell	*minishell
){
	rl_clear_history();
	ft_hashmap_clear(&minishell->variables.environment, free);
	ft_bzero(minishell, sizeof(t_minishell));
}
