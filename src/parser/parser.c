/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:38 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/23 22:53:35 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**expand_envs(char **argv);
static int	count_argv(char **argv);

char	*parse(
	char *line,
	t_minishell *minishell
){
	t_command	command;

	if (!line || !*line)
		return (NULL);
	(void)minishell;
	command.argv = expand_envs(ft_split(line, SPACE));
	command.argc = count_argv(command.argv);
	if (!command.argc)
		return (NULL);
////////////////////////////////////////////////////////////////////////////////
	//* DEBUG
	// int	i = -1;
	// while (command.argv[++i])
		// printf("argv[%i]: %s\n", i, command.argv[i]);
////////////////////////////////////////////////////////////////////////////////
	return (NULL);
}

static char	**expand_envs(
	char **argv
){
	int		i;
	char	*env;

	if (!argv)
		return (NULL);
	else if (!*argv) // check if ft_split returned and empty matrix
	{
		ft_free_split(argv);
		return (NULL);
	}
	i = -1;
	while (argv[++i])
	{
		if (!ft_strchr(argv[i], DOLLAR)
			|| (ft_strchr(argv[i], DOLLAR) && ft_strchr(argv[i], SINGLE_QUOTE) && ft_strchr(argv[i] + (ft_strchr(argv[i], SINGLE_QUOTE) + 1 - argv[i]), SINGLE_QUOTE))) // env is surrounded by single quote
			continue ;
		env = getenv(ft_strchr(argv[i], DOLLAR) + 1);
		free(argv[i]);
		if (env)
			argv[i] = ft_strdup(env);
		else
			argv[i] = ft_strdup("");
	}
	return (argv);
}

static int	count_argv(
	char **argv
){
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
