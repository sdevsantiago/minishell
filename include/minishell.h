/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 03:42:51 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/31 14:01:36 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>

# define HISTORY_FILE "/.minishell_history"

typedef struct s_env
{
	char	*home;
	char	**path;
}				t_env;

typedef struct s_minishell
{
	char	*prompt;
	char	*history_file;
	t_env	env;
}				t_minishell;

#endif
