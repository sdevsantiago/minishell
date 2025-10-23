/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:34:42 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/23 17:10:17 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(
	int argc,
	char const *argv[],
	char **envp
){
	t_minishell	minishell;
	u_int8_t	exit_status;

	if (argc != 1 || argv[1] || !envp)
	{
		printf("Usage: ./minishell\n");
		return (EXIT_FAILURE);
	}
	if (!minishell_init(&minishell, envp))
	{
		printf("Error: %s\n", "failed to initialize minishell");
		return (EXIT_FAILURE);
	}
	exit_status = minishell_run(&minishell);
	minishell_clear(&minishell);
	return (exit_status);
}
