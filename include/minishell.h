/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 03:42:51 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/03 22:56:35 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
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
	char	**envp;
}				t_cmd;

# define HISTORY_FILE "/.minishell_history"

typedef struct s_minishell
{
	char	*history_file;
	char	**envp;
}				t_minishell;

/* ******************************* Commands ********************************* */

typedef int	(*t_msh_cmdfunc)(char **args, char **env, t_minishell* minshell);

// exec.c

int		exec_cmd(char *cmd, char **args, t_minishell *minishell);

// parse.c

t_cmd	parse_cmd(char *line, t_minishell *minishell);

/* ********************************* Utils ********************************** */

// get_hostname.c
char	*get_hostname(void);

#endif
