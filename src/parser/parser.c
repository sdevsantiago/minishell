/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:38 by sede-san          #+#    #+#             */
/*   Updated: 2025/11/19 18:47:07 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../lib/Libft/libft.h"
#include "../../include/parser.h"

void	ft_parse(char *line)
{
	t_minilist	*command;
	int		quote_flag;
	int		i;

	i = 0;
	if (!line || !line[0])
		exit(1);
	quote_flag = ft_quote_detecter(line);
	if (quote_flag == 0)
		exit(1);
	if (quote_flag == 1)
		(command) = ft_minilstcreater(line);
	while((command)->content->argv[i])
	{
		printf("argumento: %s\n", (command)->content->argv[i]);
		i++;
	}
}

int ft_quote_detecter(char *line)
{
	int	result;
	int aux;

	aux = 0;
	result = 1;
	if (ft_strchr(line, SINGLE_QUOTE) || ft_strchr(line, DOUBLE_QUOTE))
	{
		ft_door(&aux, line);
		if (aux % 2 == 0)
			result = 1;
		else if (aux % 2 != 0)
		{
			printf("Comillas sin cerrar\n");
			result = 0;
		}
	}
	return (result);
}

void ft_door(int *n, char *line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == SINGLE_QUOTE)
		{
			(*n)++;
			i++;
			while (line[i] != SINGLE_QUOTE && line[i])
			i++;
			if (line[i] == SINGLE_QUOTE)
			(*n)++;
		}
		if (line[i] == DOUBLE_QUOTE)
		{
			(*n)++;
			i++;
			while (line[i] != DOUBLE_QUOTE && line[i])
			i++;
			if (line[i] == DOUBLE_QUOTE)
			(*n)++;
		}
		i++;
	}
	printf("%s\n", line);
}

t_minilist	*ft_minilstcreater(char *line)
{
	int i;
	int j;
	int k;
	t_minilist *result;

	(result) = ft_minilstnew(ft_minicommandnew());
	i = 0;
	while(line[i])
	{
		j = -1;
		k = 0;
		if (line[i] == '|')
			ft_parse_pipe(result->content, &result, line, &i);
		else if (line[i] == '>')
			ft_parse_r1(result->content, &result, line, &i);
		else if (line[i] == '<')
			ft_parse_r2(result->content, &result, line, &i);
		else//ver cuando expando
		{
			if (line[i] == DOUBLE_QUOTE)
			{
				i++;
				j++;
				while(line[i] != DOUBLE_QUOTE)
				{
					result->content->argv[j][++k] = line[++i];
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
					result->content->argv[j][++k] = line[i];
					i++;
				}
				i++;
			}
			while (line[i] != '|' && line[i] != '>' && line[i] != '<' && line[i])
			{
				j++;
				result->content->argv[j] = malloc(sizeof(char) * ft_strlen(line));
				while(!ft_isspace(line[i]) && line[i])
				{
					//hacer aqui una funciona para contaar lo que se necsita examctamete en el lloc ???? nose
					result->content->argv[j][k] = line[i];
					printf("%c\n", result->content->argv[j][k]);
					k++;
					i++;
				}
				result->content->argv[j][k] = '\0';
				while (ft_isspace(line[i]) && line[i])
					i++;
			}
			result->content->argc = j + 1;
			result->content->type = TEXT;
			ft_minilstadd_back(&result, ft_minilstnew(result->content));
		}
	}
	return(result);
}

void	ft_parse_pipe(t_command *aux, t_minilist **command, char *line, int *i)
{
	aux->argv[0][0] = line[*i];
	aux->argc = 1;
	aux->type = PIPE;
	(*i)++;
	printf("%c\n", aux->argv[0][0]);
	ft_minilstadd_back(command, ft_minilstnew(aux));
}

void	ft_parse_r1(t_command *aux, t_minilist **command, char *line, int *i)
{
	if (line[*i + 1] != '>')
	{
		aux->argv[0][0] = line[*i];
		aux->argc = 1;
		aux->type = R1;
		(*i)++;
		printf("%c\n", aux->argv[0][0]);
		ft_minilstadd_back(command, ft_minilstnew(aux));
	}
	else if (line[*i + 1] == '>')
	{
		aux->argv[0][0] = line[*i];
		aux->argv[0][1] = line[*i + 1];
		aux->argc = 1;
		aux->type = R11;
		*i = (*i) + 2;
		printf("%c\n", aux->argv[0][0]);
		printf("%c\n", aux->argv[0][1]);
		ft_minilstadd_back(command, ft_minilstnew(aux));
	}
}

void	ft_parse_r2(t_command *aux, t_minilist **command, char *line, int *i)
{
	if (line[*i + 1] != '<')
	{
		aux->argv[0][0] = line[*i];
		aux->argc = 1;
		aux->type = R1;
		(*i)++;
		printf("%c\n", aux->argv[0][0]);
		ft_minilstadd_back(command, ft_minilstnew(aux));
	}
	else if (line[*i + 1] == '<')
	{
		aux->argv[0][0] = line[*i];
		aux->argv[0][1] = line[*i + 1];
		aux->argc = 1;
		aux->type = R11;
		*i = (*i) + 2;
		printf("%c\n", aux->argv[0][0]);
		printf("%c\n", aux->argv[0][1]);
		ft_minilstadd_back(command, ft_minilstnew(aux));
	}
}

t_minilist	*ft_minilstnew(t_command *content)
{
	t_minilist	*node;

	node = (t_minilist *)malloc(sizeof(t_minilist));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

t_command	*ft_minicommandnew()
{
	t_command	*node;

	node = (t_command *)malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->argc = 0;
	node->type = 0;
	node->argv = malloc(sizeof(char *) * 100);
	return (node);
}

void	ft_minilstadd_back(t_minilist **lst, t_minilist *new)
{
	t_minilist	*lst_ptr;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		lst_ptr = ft_minilstlast(*lst);
		lst_ptr->next = new;
	}
}

t_minilist	*ft_minilstlast(t_minilist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	main()
{
	char *line = "echo hol\"a > ls -la";
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