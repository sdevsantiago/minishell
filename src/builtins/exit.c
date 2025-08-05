/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:38:18 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/05 09:39:25 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles the shell's exit builtin command.
 *
 * Prints "exit" to standard output and determines the exit code based on the
 * arguments provided.
 *
 * @param argc The number of arguments passed to the exit command.
 * @param argv The array of argument strings.
 * @return The exit code to be used by the shell.
 *
 * Behavior:
 * - If no additional arguments are provided (argc == 1), exits with code 0.
 * - If more than one argument is provided:
 *     - If the first argument is not a valid numeric string, prints an error
 *       message to stderr and exits with error code 2.
 *     - If the first argument is valid but there are too many arguments,
 *       prints an error message to stderr and returns -1. In this case the
 *       shell must not exit.
 * - Otherwise, parses the first argument as a long integer and casts it to an
 *   unsigned char, then to an unsigned int to ensure the exit code is within
 *   the range 0-255.
 */
int	exit_builtin(
	int argc,
	char const *argv[])
{
	int	exit_code;

	ft_putendl("exit");
	if (argc == 1)
		exit_code = 0;
	else
	{
		if (!ft_strisnum(argv[1]))
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", argv[1]);
			exit_code = 2;
		}
		else if (argc > 2)
		{
			fprintf(stderr, "exit: too many arguments\n");
			exit_code = -1;
		}
		else
			exit_code = (unsigned int)((unsigned char)(ft_atol(argv[1])));
	}
	return (exit_code);
}
