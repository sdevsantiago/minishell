/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 23:55:00 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/14 23:55:00 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	export_sort_entries(
	t_map_entry **entries,
	size_t count
)
{
	size_t		i;
	size_t		j;
	t_map_entry	*tmp;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp((char *)entries[i]->key, (char *)entries[j]->key) > 0)
			{
				tmp = entries[i];
				entries[i] = entries[j];
				entries[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
