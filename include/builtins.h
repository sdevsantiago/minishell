/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 22:09:51 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 01:15:34 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ft_args.h"
# include "minishell.h"
# include "core.h"
# include "variables.h"

typedef uint8_t	(*t_builtin_func)(t_command cmd, t_minishell *minishell);

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

/* builtins.c */

extern uint8_t	set_builtins(t_minishell *minishell);

extern uint8_t	is_builtin(const char *command_name, t_minishell *minishell);

/* cd.c */

extern uint8_t	builtin_cd(t_command cmd, t_minishell *minishell);

/* echo.c */

extern uint8_t	builtin_echo(t_command cmd, t_minishell *minishell);

/* exit.c */

extern uint8_t	builtin_exit(t_command cmd, t_minishell *minishell);

/* pwd.c */

extern uint8_t	builtin_pwd(t_command cmd, t_minishell *minishell);

/* env.c */

extern uint8_t	builtin_env(t_command cmd, t_minishell *minishell);

/* export.c */

extern uint8_t	builtin_export(t_command cmd, t_minishell *minishell);

/* unset.c */

extern uint8_t	builtin_unset(t_command cmd, t_minishell *minishell);

#endif /* BUILTINS_H */
