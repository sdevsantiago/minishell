/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_def.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:31:08 by sede-san          #+#    #+#             */
/*   Updated: 2025/11/02 03:11:10 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_DEF_H
# define ECHO_DEF_H

# include "builtins.h"

typedef struct s_args
{
	t_arg	no_newline;
	t_arg	strings;
}	t_args;

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

// echo_def.c

extern t_args	read_args(t_command cmd);

#endif /* ECHO_DEF_H */
