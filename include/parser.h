/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:03:51 by sede-san          #+#    #+#             */
/*   Updated: 2025/11/11 15:10:29 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/******************************************************************************/
/*                           Structures & Data Types                          */
/******************************************************************************/

typedef struct s_command
{
	int		argc;
	char	**argv;
	int		type;
	
}	t_command;


enum	e_token
{
	TEXT,
	PIPE,
	R1,
	R2,
	R11,
	R22,
}	t_token;

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

// parser.c

extern char	*parse(char *line, t_minishell *minishell);
int ft_door(char *line);
t_command	ft_comiller(t_command com);
char	*ft_cleaner(char *line);

#endif /* PARSER_H */
