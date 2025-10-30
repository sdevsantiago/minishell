/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 22:09:51 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/30 12:06:39 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

// exit.c

extern u_int8_t	builtin_exit(t_command cmd, t_minishell *msh);

// pwd.c

extern u_int8_t	builtin_pwd(t_command cmd, t_minishell *msh);

#endif /* BUILTINS_H */
