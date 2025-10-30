/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:10:13 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/30 12:46:15 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "minishell.h"

/******************************************************************************/
/*                           Structures & Data Types                          */
/******************************************************************************/

typedef struct s_minishell	t_minishell;
typedef struct s_variables	t_variables;
typedef struct s_command	t_command;

/**
 * @brief Structure that holds both environment and internal variables
 *
 * This structure contains pointers to arrays of strings that represent
 * different types of variables used in the minishell program.
 *
 * @param environment Array of environment variable strings (NULL-terminated)
//// @param intp Array of internal variable strings (NULL-terminated)
 */
typedef struct s_variables
{
	char	**environment;
	// char	**internal;
}	t_variables;

/**
 * @brief Main minishell structure containing global state information
 *
 * This structure holds the essential data for the minishell program.
 *
 * @param variables Structure that holds both environment and internal variables
 * @param exit_status Exit status code of the last executed command (0-255)
 */
typedef struct s_minishell
{
	t_variables	variables;
	u_int8_t	exit_status;
}	t_minishell;

/**
 * @brief Structure representing a single command in the shell
 *
 * This structure holds all the necessary information for executing a command
 * in the minishell, including its arguments and executable path.
 *
 * @param argc Number of arguments in the command (including the command name)
 * @param argv Array of strings containing the command and its arguments
 * @param path Full path to the executable file for this command
 */
typedef struct s_command
{
	int		argc;
	char	**argv;
	char	*path;
}	t_command;

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

/* minishell.c */

extern int		minishell_init(t_minishell *minishell, char **envp);

extern u_int8_t	minishell_run(t_minishell *minishell);

extern void		minishell_clear(t_minishell *minishell);

#endif /* CORE_H */
