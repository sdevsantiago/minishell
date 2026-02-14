/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 22:28:01 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 01:11:38 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"
# include "core.h"
# include "parser.h"

extern void	syntax_error_unexpected_token(t_token *token);
extern void	malloc_error(void);
extern void	command_not_found_error(const char *command);

#endif /* ERRORS_H */