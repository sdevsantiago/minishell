/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:38 by sede-san          #+#    #+#             */
/*   Updated: 2025/11/12 16:30:38 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_parse(char *line)
{
	t_list	**command;
	int		quote_flag;// 0 = comillas si cerrar 1 = comillas cerradas/sin comillas
	if (!line || !line[0])
		return (NULL);
	quote_flag = ft_quote_detecter(line);
	if (quote_flag == 0)
		exit(1);
	if (quote_flag == 1)
		command = ft_com_creater(command, line);
}

int ft_quote_detecter(char *line)
{
	int	result;
	int aux;

	aux = 0;
	result = 0;
	if (strchr(line, SINGLE_QUOTE) || strchr(line, DOUBLE_QUOTE))
	{
		aux = ft_door(line);
		if (aux != 0 && aux % 2 == 0)
			result = 1;
		else if (aux % 2 != 0)
		{
			printf("Comillas sin cerrar\n");
			result = 2;
		}
	}
	return (result);
}

int ft_door( char *line)//comillas abiertas o cerradas
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

t_list	**ft_com_creater(t_list **command, char *line)//con comillas
{
	int i;
	int j;
	int k;
	t_command	*aux;

	i = 0;
	while(line[i])
	{
		j = -1;
		k = -1;
		
		if (line[i] == '|')//si es espcial guardar -> hacer ft propia
		{
			aux->argv[0][0] = line[i];
			aux->argc = 1;
			aux->type = PIPE;
			ft_lstadd_back(command, ft_lstnew(aux));
			i++;
		}
		else if (line[i] == '>' && line[i + 1] != '>')
		{
			aux->argv[0][0] == line[i];
			aux->argc = 1;
			aux->type = R1;
			ft_lstadd_back(command, ft_lstnew(aux));
			i++;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			aux->argv[0][0] == line[i];
			aux->argv[0][1] == line[i + 1];
			aux->argc = 1;
			aux->type = R11;
			ft_lstadd_back(command, ft_lstnew(aux));
			i = i + 2;
		}
		else if (line[i] == '<' && line[i + 1] != '<')
		{
			aux->argv[0][0] == line[i];
			aux->type = R2;
			aux->argc = 1;
			ft_lstadd_back(command, ft_lstnew(aux));
			i++;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			aux->argv[0][0] == line[i];
			aux->argv[0][1] == line[i + 1];
			aux->type = R22;
			ft_lstadd_back(command, ft_lstnew(aux));
			i = i + 2;
		}
		else//ver cuando expando
		{
			if (line[i] == DOUBLE_QUOTE)
			{
				i++;
				j++;
				while(line[i] != DOUBLE_QUOTE)
				{
					aux->argv[j][++k] = line[i];
					i++;
				}
				i++;
			}
			if (line[i] == SINGLE_QUOTE)
			{
				i++;
				j++;
				while(line[i] != SINGLE_QUOTE)
				{
					aux->argv[j][++k] = line[i];
					i++;
				}
				i++;
			}
			
			while(line[i] != '|' && line[i] != '>' && line[i] != '<')
			{
				j++;
				while(!ft_isspace(line[i]))
					aux->argv[j][++k] = line[i];
				if (ft_isspace(line[i]))
					i++;
			}
			aux->argc = j + 1;
			aux->type = TEXT;
			ft_lstadd_back(command, ft_lstnew(aux));
		}
	}
	return(command);
}
/* 
static char	**expand_envs(char **argv);
static int	count_argv(char **argv);

void parse(char *line, t_minishell *minishell)
{
	t_command	command;

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
*/