/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:10:13 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 01:25:43 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "minishell.h"

/******************************************************************************/
/*                           Structures & Data Types                          */
/******************************************************************************/

# define TOKENS_COUNT 5

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef enum e_redirection_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC
}	t_redirection_type;

typedef struct s_redirection
{
	t_token_type	type;
	int				io_number;
	char			*target;
	bool			heredoc_expand;
	bool			heredoc_ready;
}	t_redirection;

/**
 * @brief Structure that holds both environment and internal variables
 *
 * This structure contains pointers to arrays of strings that represent
 * different types of variables used in the minishell program.
 *
 * @param environment Array of environment variable strings (NULL-terminated)
//// @param intp Array of internal variable strings (NULL-terminated)
 */
typedef struct s_variables
{
	t_hashmap	*environment;
	t_hashmap	*internal;
}	t_variables;

/**
 * @brief Main minishell structure containing global state information
 *
 * This structure holds the essential data for the minishell program.
 *
 * @param variables Structure that holds both environment and internal variables
 * @param exit_status Exit status code of the last executed command (0-255)
 */
typedef struct s_minishell
{
	t_variables	variables;
	t_hashmap	*builtins;
	uint8_t		exit_status;
	bool		exit;
}	t_minishell;

/**
 * @brief Structure representing a single command in the shell
 *
 * This structure holds all the necessary information for executing a command
 * in the minishell, including its arguments and executable path.
 *
 * @param argc Number of arguments in the command (including the command name)
 * @param argv Array of strings containing the command and its arguments
 * @param path Full path to the executable file for this command
 */
typedef struct s_command
{
	int		argc;
	char	**argv;
	char	*path;
	t_list	*redirections;
	t_list	*heredocs;
}	t_command;

/**
 * @brief Default shell prompt string
 */
# define DEFAULT_PS1 "minishell > "

/**
 * @brief Default secondary prompt string for multiline input
 */
# define DEFAULT_PS2 "> "

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

/* minishell.c */

extern void		minishell_init(t_minishell *minishell, char **envp);

extern void		minishell_run(t_minishell *minishell);

extern void		minishell_clear(t_minishell *minishell);

extern void		minishell_set_interactive_signals(void);

extern void		minishell_set_execution_signals(void);

extern void		minishell_set_child_signals(void);

extern void		minishell_set_heredoc_signals(void);

extern bool		minishell_consume_sigint(void);

/* environment.c */

extern void		set_envp(char **envp, t_minishell *msh);

extern void		set_env(const char *env_name, char *env_value,
					t_minishell *msh);

extern char		**get_envp(t_minishell *msh);

extern void		free_envp(char **envp);

extern void		handle_sigint_status(t_minishell *minishell);
extern bool		handle_eof(char *line, t_minishell *minishell);

#endif /* CORE_H */
