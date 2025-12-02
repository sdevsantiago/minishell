/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 22:09:51 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/02 20:47:03 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "minishell.h"
# include "ft_args.h"

typedef unsigned char	(*t_builtin_func)(t_command cmd, t_minishell *msh);

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

/* builtins.c */

extern u_int8_t	set_builtins(t_minishell *msh);

extern u_int8_t	is_builtin(const char *command_name, t_minishell *msh);

/* cd.c */

extern u_int8_t	builtin_cd(t_command cmd, t_minishell *msh);

/* echo.c */

extern u_int8_t	builtin_echo(t_command cmd, t_minishell *msh);

/* exit.c */

extern u_int8_t	builtin_exit(t_command cmd, t_minishell *msh);

/* pwd.c */

extern u_int8_t	builtin_pwd(t_command cmd, t_minishell *msh);

/* unset.c */

extern u_int8_t	builtin_unset(t_command cmd, t_minishell *msh);

#endif /* BUILTINS_H */
