/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:10:13 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/22 19:27:19 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "minishell.h"

/******************************************************************************/
/*                           Structures & Data Types                          */
/******************************************************************************/

typedef struct s_minishell	t_minishell;

/**
 * @brief Main minishell structure containing global state information
 *
 * This structure holds the essential data for the minishell program,
 * including the environment variables and the exit status of the last
 * executed command.
 *
 * @param env Array of environment variable strings in "KEY=VALUE" format
 * @param exit_status Exit status code of the last executed command (0-255)
 */
typedef struct s_minishell
{
	char			**env;
	u_int8_t		exit_status;
}	t_minishell;

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

/* minishell.c */

extern int		minishell_init(t_minishell *minishell, char **envp);

extern u_int8_t	minishell_run(t_minishell *minishell);

extern void		minishell_clear(t_minishell *minishell);

#endif /* CORE_H */
