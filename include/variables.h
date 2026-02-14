/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:45:35 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 01:24:49 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# include "minishell.h"
# include "core.h"

// variables.c

extern char		*get_var(const char *name, t_minishell *minishell);
extern void		set_var(const char *name, char *value, t_minishell *minishell);
extern void		unset_var(const char *name, t_minishell *minishell);

// environment.c

extern char		*get_env(const char *name, t_minishell *minishell);
extern void		set_env(const char *name, char *value, t_minishell *minishell);
extern void		unset_env(const char *name, t_minishell *minishell);

extern void		set_envp(char **envp, t_minishell *minishell);
extern char		**get_envp(t_minishell *minishell);
extern void		free_envp(char **envp);

// internal.c

extern char		*get_int(const char *name, t_minishell *minishell);
extern void		set_int(const char *name, char *value, t_minishell *minishell);
extern void		unset_int(const char *name, t_minishell *minishell);

extern void		set_intp(t_minishell *minishell);

#endif /* VARIABLES_H */
