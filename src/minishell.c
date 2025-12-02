/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:51:33 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/01 19:02:18 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_init(
	t_minishell	*minishell,
	char		**envp
){
	ft_bzero(minishell, sizeof(t_minishell));
	set_envp(envp, minishell);
	set_builtins(minishell);
	if (minishell->variables.environment == NULL || minishell->builtins == NULL)
	{
		minishell_clear(minishell);
		return (0);
	}
	return (1);
}

u_int8_t	minishell_run(
	t_minishell	*minishell
){
	char		*line;
	t_command	command;

	line = NULL;
	while (minishell->exit == 0)
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
	if (minishell->variables.environment != NULL)
		ft_hashmap_clear(&minishell->variables.environment, free);
	if (minishell->builtins != NULL)
		ft_hashmap_clear_keys(&minishell->builtins);
	ft_bzero(minishell, sizeof(t_minishell));
}
