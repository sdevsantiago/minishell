/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:18:21 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/02 17:55:22 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <string.h>
# include <stdio.h>

typedef int	(*t_builtin_func)(int argc, char const *argv[]);

typedef struct s_builtin
{
	const char		*name;
	t_builtin_func	function;
}				t_builtin;

// cd.c

int	cd_builtin(int argc, char const *argv[]);

// echo.c

typedef struct s_echo_flags
{
	int	newline;	// print newline after everything has been printed
}				t_echo_flags;

int	echo_builtin(int argc, char const *argv[]);

// env.c

int	env_builtin(int argc, char const *argv[]);

// exit.c

int	exit_builtin(int argc, char const *argv[]);

// export.c

int	export_builtin(int argc, char const *argv[]);

// pwd.c

int	pwd_builtin(int argc, char const *argv[]);

// unset.c

int	unset_builtin(int argc, char const *argv[]);

#endif
