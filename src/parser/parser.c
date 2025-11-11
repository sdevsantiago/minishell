/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:38 by sede-san          #+#    #+#             */
/*   Updated: 2025/11/11 18:17:25 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_parse(char *line)
{
	t_list	*command;
	int		quote_flag;// 0 = no hay comillas, 1 = hay comillas, 2 = comillas sin cerrar
	if (!line || !line[0])
		return (NULL);
	command = ft_init_list();
	quote_flag = ft_quote_unquote(line);
	if (quote_flag == 2)
		exit(1);
	if (quote_flag == 0)//si no hay comillas 
	//1. emepzar a leer hasta encontrar (mientras no haya comillas) un pipe / redirección / null 
	//2. ir guardando en el argv (si hya comillas empezar a guardar en argv[0])
	//3. si hay variables de entorno ver si se tiene que expandir y expandirlas/no expandirlas
	

}
t_list	*ft_init_list()
{
	t_list	*node;
	t_command *model;

	model->argc = 0;
	model->argv = NULL;
	model->type = 0;
	node = ft_lstnew(model);
	return (node);
}

int ft_quote_unquote(char *line)
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

t_list	*ft_split_0(t_list **command, char *line)
{
	int i;
	int j;
	int k;
	t_command	*aux;

	i = 0;
	j = 0;
	k = 0;
	while(line[i])
	{
/* 		while (line[i] != '|' || line [i] != '<' || line[i] != '>')//tengo que repasar el push swap pq no me acuerod de las lsitas
		{
			if (ft_isspace(line[i]))
			{
				j++;
				k = 0;
				while (ft_isspace(line[i]))
					i++;
			}
			command->content->argv[j][k] == line[i];
			command->content->type = TEXT;
			i++;
			k++;
		} */
		if (line[i] == '|')//si es espcial guardar -> hacer ft propia
		{
			aux->argv[0][0] == line[i];
			aux->type = PIPE;
			ft_lstadd_back(command, ft_lstnew(aux));
			i++;
		}
		else if (line[i] == '>' && line[i + 1] != '>')
		{
			aux->argv[0][0] == line[i];
			aux->type = R1;
			ft_lstadd_back(command, ft_lstnew(aux));
			i++;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			aux->argv[0][0] == line[i];
			aux->argv[0][1] == line[i + 1];
			aux->type = R11;
			ft_lstadd_back(command, ft_lstnew(aux));
			i = i + 2;
		}
		else if (line[i] == '<' && line[i + 1] != '<')
		{
			aux->argv[0][0] == line[i];
			aux->type = R2;
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
	}
}
/* void	ft_divider(t_command *com, char *line)
{
	int i;
	int j;
	int c;
	t_command	*aux;
	
	i = 0;
	j = 0;
	while (line[i])
	{
		char *aux;
		if (line[i] == DOUBLE_QUOTE)
		{
			i++;
			while (line[i] != DOUBLE_QUOTE && line[i])
			{
				aux[j] = line[i];
				i++;
				j++;
			}
			if (!line[i])
				break ;
			com->name = aux;//luego hago esto
			com->type = TEXT;
			ft_comadd_back(&com, aux);
			free(aux);
			
		}
		else if (line[i] == SINGLE_QUOTE)
		{
			i++;
			while (line[i] != SINGLE_QUOTE && line[i])
			{
				aux[j] = line[i];
				i++;
				j++;
			}
			if (!line[i])
				break ;
			com->name = aux;//luego hago esto
			com->type = TEXT;
			ft_comadd_back(&com, aux);
			free(aux);
		}
		else if (line[i] == SPACE)//o tabulador o algo asi
		{
			while (line[i] == SPACE && line[i])
				i++;
		}
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')//comprobar si es pie o redirección o klk
		{
			if (line[i] == '|')
			{
				com->name = line[i];//luego hago esto
				com->type = PIPE;
				ft_comadd_back(&com, aux);
			}
			if (line[i] == '>')
			{ 
				if (line[i + 1] == '<')
					break ;
				if(line[i + 1] != '>')
				{
					com->name = ">>";//luego hago esto
					com->type = R11;
					ft_comadd_back(&com, aux);
					i = i + 2;
				}
				com->name = '>';//luego hago esto
				com->type = R1;
				ft_comadd_back(&com, aux);
			}
			
		}
		i++;
	}
} */



/* 
static char	**expand_envs(char **argv);
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