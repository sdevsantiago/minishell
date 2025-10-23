/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:51:33 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/23 14:14:30 by sede-san         ###   ########.fr       */
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
	char	*line;

	while (1)
	{
		line = readline("minishell > ");
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		parse(line, minishell);
		if (!ft_strcmp(line, "exit"))
			break ;
		// printf("%s\n", line);
		free(line);
	}
	free(line);
	return (minishell->exit_status);
}

void	minishell_clear(
	t_minishell	*minishell
){
	rl_clear_history();
	ft_bzero(minishell, sizeof(t_minishell));
}
