/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:22:11 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/05 09:22:15 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_echo_flags	set_flags(char const *argv[], size_t *i);
static void			set_default_flags(t_echo_flags *flags);

/**
 * @brief Executes the echo builtin command.
 *
 * This function processes the arguments passed to the echo command,
 * handles any flags (such as -n for no trailing newline), and prints
 * the arguments to standard output separated by spaces.
 *
 * @param argc The number of arguments in argv.
 * @param argv The array of argument strings, with argv[0] being "echo".
 *
 * @return EXIT_SUCCESS on successful execution.
 */
int	echo_builtin(
	int argc,
	char const *argv[])
{
	t_echo_flags	flags;
	size_t			i;

	(void)argc;
	flags = set_flags(argv, &i);
	while (argv[i])
	{
		ft_putstr((char *)argv[i]);
		if (argv[++i])
			ft_putchar(' ');
	}
	if (flags.newline)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}

/**
 * @brief Parses command-line arguments to set flags for the echo builtin.
 *
 * This function examines the arguments passed to the echo command, starting
 * from argv[1], and sets the appropriate flags based on the presence of
 * options (e.g., "-n"). It updates the index `i` to point to the first
 * non-option argument.
 *
 * @param argv Array of argument strings (NULL-terminated).
 * @param i    Pointer to a size_t variable that will be updated to the index
 *             of the first non-option argument.
 *
 * @return t_echo_flags Structure containing the parsed flags (e.g., whether
 *                      to print a trailing newline).
 */
static t_echo_flags	set_flags(
	char const *argv[],
	size_t *i
)
{
	t_echo_flags	flags;
	size_t			j;

	set_default_flags(&flags);
	*i = 1;
	if (!argv[1])
		return (flags);
	while (*argv[*i] == '-')
	{
		j = 1;
		if (!argv[*i][j])
			return (flags);
		while (argv[*i][j])
		{
			if (argv[*i][j] == 'n')
				flags.newline = 0;
			else
				return (set_default_flags(&flags), flags);
			j++;
		}
		(*i)++;
	}
	return (flags);
}

/**
 * @brief Initializes the t_echo_flags structure with default values.
 *
 * This function zeroes out all fields of the given t_echo_flags structure
 * and sets the 'newline' flag to 1, indicating that a newline should be
 * printed by default.
 *
 * @param flags Pointer to the t_echo_flags structure to initialize.
 */
static void	set_default_flags(t_echo_flags *flags)
{
	ft_bzero(flags, sizeof(t_echo_flags));
	flags->newline = 1;
}
