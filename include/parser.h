/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:03:51 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/12 18:34:11 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "core.h"
# include "builtins.h"

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

// parser.c

extern t_list		*parse(char *line, t_minishell *minishell);

// lexer.c

t_token_type		get_token_type(const char *str);
t_token				*token_new(t_token_type type, char *text);
t_token				*read_token(t_token_type type, const char *line,
						size_t *i);
t_token				*read_word(const char *line, size_t *i);

extern t_list		*lex(const char *line);

extern void			token_clear(t_token *token);
extern t_command	*command_new(t_list **tokens);
extern void			command_clear(t_command *command);
extern void			command_add_tokens(t_command **command, t_list **tokens);
extern bool			is_pipe(t_token *token);
extern bool			is_redirection(t_token *token);
bool				parser_token_is_fd_prefix(t_list *token_node,
						int *io_number);
void				redirection_add_with_fd(t_list **tokens, t_token *token,
						t_command **command, int io_number);
void				words_add(t_list **tokens, t_command **command);

void				expand(t_list **commands, t_minishell *minishell);
void				redirection_clear(t_redirection *redirection);

#endif /* PARSER_H */
