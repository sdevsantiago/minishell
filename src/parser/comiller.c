/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comiller.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:31:31 by padan-pe          #+#    #+#             */
/*   Updated: 2025/10/28 19:00:46 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int ft_door(char *line)//abiertas o cerradas
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

char	**ft_comiller(char **argv)//si es par = cerradas
{
	int n;
	char *result;
	int i;

	i = 0;
	while (argv[i])
	{
		n = ft_door(argv[i]);
		if (n % 2 == 0)
		{
			if (n == 0)
				result = argv[i];
			else
				result = ft_cleaner(argv[i]);
			return (result);
		}
		else
		{
			printf("Error: comillas sin cerrar\n");
			return ;	
		}
	}
	return (argv);
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
		if (line[i] == DOUBLE_QUOTE)
		{
			while (line[++i] != DOUBLE_QUOTE && line[i])
				aux[++n] = line[i];
		}
		else
			aux[++n] = line[i];
	}
	return (aux);
}
