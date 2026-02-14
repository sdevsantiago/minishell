/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:51:33 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 12:57:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core.h"
#include "parser.h"
#include "executor.h"

void	minishell_init(
	t_minishell	*minishell,
	char		**envp
){
	ft_bzero(minishell, sizeof(t_minishell));
	set_intp(minishell);
	set_envp(envp, minishell);
	set_builtins(minishell);
	if (minishell->variables.environment == NULL || minishell->builtins == NULL)
		minishell_clear(minishell);
}

void	minishell_run(
	t_minishell	*minishell
)
{
	char	*line;
	t_list	*commands;

	if (minishell == NULL)
		return ;
	minishell_set_interactive_signals();
	while (!minishell->exit)
	{
		if (isatty(STDIN_FILENO))
			line = readline(get_var("PS1", minishell));
		else
			line = get_next_line(STDIN_FILENO);
		handle_sigint_status(minishell);
		if (handle_eof(line, minishell))
			continue ;
		if (*line != '\0')
		{
			add_history(line);
			commands = parse(line, minishell);
			minishell->exit_status = execute(commands, minishell);
		}
		free(line);
	}
}

void	minishell_clear(
	t_minishell	*minishell
){
	rl_clear_history();
	if (minishell->variables.internal != NULL)
		ft_hashmap_clear(&minishell->variables.internal, free);
	if (minishell->variables.environment != NULL)
		ft_hashmap_clear(&minishell->variables.environment, free);
	if (minishell->builtins != NULL)
		ft_hashmap_clear_keys(&minishell->builtins);
}
