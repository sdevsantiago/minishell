/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 22:09:51 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/31 00:11:04 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

// cd.c

extern u_int8_t	builtin_cd(t_command cmd, t_minishell *msh);

// exit.c

extern u_int8_t	builtin_exit(t_command cmd, t_minishell *msh);

// pwd.c

extern u_int8_t	builtin_pwd(t_command cmd, t_minishell *msh);

#endif /* BUILTINS_H */
