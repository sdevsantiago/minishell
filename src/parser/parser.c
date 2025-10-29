/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:38 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/29 19:12:30 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static char	**expand_envs(char **argv);
static int	count_argv(char **argv);

void parse(char *line, t_minishell *minishell)
{
	t_command	command;// argc y argv y ¿flag para eoandir?

	if (!line || !line[0])
		return (NULL);
	//1. organizar
	if (ft_line_parse(line))
		command.argv = ft_split(line, SPACE);
	
	command = ft_comiller(command);
	command.argc = count_argv(command.argv);
	if (!command.argc)
		return (NULL);
	return (NULL);
}

int	ft_line_parse(char *line)//compruebo carácteres especiales, comillas y ¿pipe?
{
	if (ft_strrchr(line, ))
	if (ft_door(line) == 0)
		return (1);
	if (ft_door(line) % 2 == 0)
		return (0);
	printf("Error: comillas sin cerrar\n");
	exit(1);
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

int ft_door(char *line)//comillas abiertas o cerradas
{
	int i;
	int n;
	
	n = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == SINGLE_QUOTE)
		{
			n++;
			i++;
			while (line[i] != SINGLE_QUOTE && line[i])
				i++;
			if (line[i] == SINGLE_QUOTE)
				n++;
		}
		if (line[i] == DOUBLE_QUOTE)
		{
			n++;
			i++;
			while (line[i] != DOUBLE_QUOTE && line[i])
				i++;
			if (line[i] == DOUBLE_QUOTE)
				n++;
		}
	}
	return (n);
}


t_command	ft_comiller(t_command com)//si es par = cerradas
{
	int flag;
	char *result;
	int i;

	flag = 1;
	i = 0;
	while (com.argv[i])
	{
		if (ft_door(com.argv[i]) % 2 == 0)
		{
			if (ft_door(com.argv[i]) == 0)
				result = com.argv[i];
			else
			{
				ft_expand(com.argv[i], flag);
				result = ft_cleaner(com.argv[i]);
			}
		}
		else
		{
			printf("Error: comillas sin cerrar\n");
			return ;	
		}
		i++;
	}
	com.exp = flag;
	return (com);
}

char	*ft_cleaner(char *line)//una vez sabiendo que hay y que están cerradas
{
	int i;
	int n;
	char *aux;
	
	n = -1;
	i = -1;
	aux = malloc(strlen(line));
	while (line[++i])
	{
		if (line[i] == SINGLE_QUOTE)
		{
			while (line[++i] != SINGLE_QUOTE && line[i])
				aux[++n] = line[i];
		}
		else if (line[i] == DOUBLE_QUOTE)
		{
			while (line[++i] != DOUBLE_QUOTE && line[i])
				aux[++n] = line[i];
		}
		else
			aux[++n] = line[i];
	}
	return (aux);
}

void	ft_expand(char *line, int flag)//asumiendo que hay y que están cerradas 1 = expandir 0 = no epandir
{
	int i;

	i = 0;
	if (!ft_strchr(line, DOLLAR))
		return (flag);
	while (line[i])
	{
		if (line[i] == SINGLE_QUOTE)
		{
			i++;
			while (line[i] != SINGLE_QUOTE)
				i++;
			if (line[i] == SINGLE_QUOTE)
				flag = 0;
		}
		else if (line[i] == DOUBLE_QUOTE)
		{
			while (line[++i] != DOUBLE_QUOTE && line[i])
				i++;
		}
		i++;
	}
}

 */