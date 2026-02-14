/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 06:56:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 06:56:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_EXPAND_INTERNAL_H
# define PARSER_EXPAND_INTERNAL_H

# include "parser.h"
# include "errors.h"
# include "variables.h"

typedef struct s_fields_ctx	t_fields_ctx;

void	parser_expand_malloc_error(t_minishell *minishell);
char	*parser_expand_variable(const char *word, size_t *i,
			t_minishell *minishell);
char	*parser_expand_word(const char *word, t_minishell *minishell,
			bool expand_vars);
bool	parser_expand_word_fields(const char *word, t_minishell *minishell,
			bool expand_vars, t_list **fields);
bool	parser_fields_append_text(char **current, const char *value,
			t_minishell *minishell);
bool	parser_fields_push_field(t_fields_ctx ctx);
bool	parser_fields_expand_unquoted_value(t_fields_ctx ctx,
			const char *expanded);
bool	parser_fields_step(const char *word, size_t *i, t_fields_ctx ctx);
bool	parser_fields_handle_backslash(const char *word, size_t *i,
			t_fields_ctx ctx, bool *handled);
bool	parser_fields_expand_tilde(const char *word, size_t *i,
			t_fields_ctx ctx, bool *handled);

typedef struct s_word_ctx
{
	char		**result;
	bool		*in_single_quote;
	bool		*in_double_quote;
	t_minishell	*minishell;
	bool		expand_vars;
}	t_word_ctx;

typedef struct s_fields_ctx
{
	t_list		**fields;
	char		**current;
	bool		*touched;
	bool		*in_single_quote;
	bool		*in_double_quote;
	t_minishell	*minishell;
	bool		expand_vars;
}	t_fields_ctx;

typedef struct s_field_state
{
	bool	touched;
	bool	in_single_quote;
	bool	in_double_quote;
}	t_field_state;

#endif
