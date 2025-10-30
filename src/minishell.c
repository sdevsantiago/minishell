/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:51:33 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/30 22:36:03 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_init(
	t_minishell	*minishell,
	char		**envp
){
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->variables.environment = envp;
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
	ft_bzero(minishell, sizeof(t_minishell));
}
