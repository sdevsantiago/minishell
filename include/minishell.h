/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 03:42:51 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/21 14:55:18 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "history.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	int		argc;
	char	**argv;
}	t_cmd;

typedef struct s_history
{
	char		*hist_file;
	size_t		hist_file_size;
	t_cdlist	hist;
	size_t		hist_size;
}	t_history;

typedef struct s_minishell
{
	char		**envp;
	t_history	*history;
	char		*history_file;
}	t_minishell;

/* ******************************** Features ******************************** */

/* History */

// history.c
void	ms_add_history(const char *line);
int		ms_read_history(const char *hist_file);
void	ms_write_history(const char *hist_file);

/* ******************************* Commands ********************************* */

// command_utils.c

int		is_absolutepath(char const *cmd);
int		is_builtin(t_cmd *cmd);
int		is_local(char const *cmd);

// exec.c

int		exec_cmd(t_cmd *cmd, char **envp);
int		exec_builtin(t_cmd *cmd, char **envp);

// parse.c

t_cmd	parse_cmd(char *line, t_minishell *minishell);

// signals.c

void	init_signal(void);

/* ********************************* Utils ********************************** */

// get_hostname.c
char	*get_hostname(void);

/* ******************************** Builtins ******************************** */

// builtin_utils.c
int		is_builtin(t_cmd *cmd);

#endif
