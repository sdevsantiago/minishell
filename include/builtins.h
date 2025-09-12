/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:18:21 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/20 22:22:40 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <string.h>
# include <stdio.h>

// cd.c

int	cd_builtin(int argc, char const *argv[]);

# define CD_HELP

// echo.c

typedef struct s_echo_flags
{
	int	newline;	// print newline after everything has been printed
}				t_echo_flags;

int	echo_builtin(int argc, char const *argv[]);

# define ECHO_HELP

// // env.c

// int	env_builtin(int argc, char const *argv[], char **envp);

// exit.c

int	exit_builtin(int argc, char const *argv[]);

# define EXIT_HELP

// export.c

int	export_builtin(int argc, char const *argv[], char **envp);

# define EXPORT_HELP

// printenv.c

int	printenv_builtin(int argc, char const *argv[], char const *envp[]);

# define PRINTENV_HELP

// pwd.c

int	pwd_builtin(int argc, char const *argv[]);

# define PWD_HELP

// unset.c

int	unset_builtin(int argc, char const *argv[], char **envp);

# define UNSET_HELP

#endif
