/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:38 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/28 18:47:34 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**expand_envs(char **argv);
static int	count_argv(char **argv);

char	*parse(char *line, t_minishell *minishell)
{
	t_command	command;// argc y argv

	if (!line || !*line)
		return (NULL);
	(void)minishell;
	command.argv = expand_envs(ft_comiller(ft_split(line, SPACE)));
	command.argc = count_argv(command.argv);
	if (!command.argc)
		return (NULL);
/* 	* DEBUG
	 int	i = -1;
	 while (command.argv[++i])
		 printf("argv[%i]: %s\n", i, command.argv[i]); */
	return (NULL);
}

static char	**expand_envs(char **argv)
{
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
		env = getenv(ft_strchr(argv[i], DOLLAR) + 1);//hacer propio getenv porque este no expande las variables creadas
		free(argv[i]);
		if (env)
			argv[i] = ft_strdup(env);
		else
			argv[i] = ft_strdup("");
	}
	return (argv);
}

static int	count_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
