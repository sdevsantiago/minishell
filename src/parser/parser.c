/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:38 by sede-san          #+#    #+#             */
/*   Updated: 2025/11/14 19:51:04 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../lib/Libft/libft.h"


void	ft_parse(char *line)
{
	t_list	**command;
	int		quote_flag;
	int		i;
	t_command	*aux;

	if (!line || !line[0])
		exit(1);
	quote_flag = ft_quote_detecter(line);
	if (quote_flag == 0)
		exit(1);
	if (quote_flag == 1)
		command = ft_lstcreater(command, line);
	while(*command)
	{
		aux = (*command)->content;
		i = 0;
		while(aux->argv[i])
		{
			printf("argumento:%s\n", aux->argv[i]);
			i++;
		}
		*command = (*command)->next;
	}
}

int ft_quote_detecter(char *line)
{
	int	result;
	int aux;

	aux = 0;
	result = 1;
	if (strchr(line, SINGLE_QUOTE) || strchr(line, DOUBLE_QUOTE))
	{
		ft_door(aux, line);
		if (aux != 0 && aux % 2 == 0)
			result = 1;
		else if (aux % 2 != 0)
		{
			printf("Comillas sin cerrar\n");
			result = 0;
		}
	}
	return (result);
}

void ft_door(int n, char *line)
{
	int i;
	
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
}

t_list	**ft_lstcreater(t_list **command, char *line)
{
	int i;
	int j;
	int k;
	t_command	aux;

	i = 0;
	while(line[i])
	{
		j = -1;
		k = 0;
		if (line[i] == '|')
			ft_parse_pipe(&aux, command, line, &i);
		else if (line[i] == '>')
			ft_parse_r1(&aux, command, line, &i);
		else if (line[i] == '<')
			ft_parse_r2(&aux, command, line, &i);
		else//ver cuando expando
		{
			if (line[i] == DOUBLE_QUOTE)
			{
				i++;
				j++;
				while(line[i] != DOUBLE_QUOTE)
				{
					aux.argv[j][++k] = line[++i];
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
					aux.argv[j][++k] = line[i];
					i++;
				}
				i++;
			}
			while (line[i] != '|' && line[i] != '>' && line[i] != '<')
			{
				j++;
				while(!ft_isspace(line[i]))
				{
					aux.argv[j][k] = line[i];
					printf("%c\n", aux.argv[j][k]);
					k++;
					i++;
				}
				while (ft_isspace(line[i]))
					i++;
			}
			aux.argc = j + 1;
			aux.type = TEXT;
			ft_lstadd_back(command, ft_lstnew(&aux));
		}
	}
	return(command);
}

void	ft_parse_pipe(t_command *aux, t_list **command, char *line, int *i)
{
	aux->argv[0][0] = line[*i];
	aux->argc = 1;
	aux->type = PIPE;
	(*i)++;
	ft_lstadd_back(command, ft_lstnew(aux));
}

void	ft_parse_r1(t_command *aux, t_list **command, char *line, int *i)
{
	if (line[*i + 1] != '>')
	{
		aux->argv[0][0] = line[*i];
		aux->argc = 1;
		aux->type = R1;
		(*i)++;
		ft_lstadd_back(command, ft_lstnew(aux));
	}
	else if (line[*i + 1] == '>')
	{
		aux->argv[0][0] = line[*i];
		aux->argv[0][1] = line[*i + 1];
		aux->argc = 1;
		aux->type = R11;
		*i = (*i) + 2;
		ft_lstadd_back(command, ft_lstnew(aux));
	}
}

void	ft_parse_r2(t_command *aux, t_list **command, char *line, int *i)
{
	if (line[*i + 1] != '<')
	{
		aux->argv[0][0] = line[*i];
		aux->argc = 1;
		aux->type = R1;
		(*i)++;
		ft_lstadd_back(command, ft_lstnew(aux));
	}
	else if (line[*i + 1] == '<')
	{
		aux->argv[0][0] = line[*i];
		aux->argv[0][1] = line[*i + 1];
		aux->argc = 1;
		aux->type = R11;
		*i = (*i) + 2;
		ft_lstadd_back(command, ft_lstnew(aux));
	}
}

int	main()
{
	char *line = "echo hola > ls -la";
	ft_parse(line);
}
/* 

static char	**expand_envs(char **argv)e
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
*/