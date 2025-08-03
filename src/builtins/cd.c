/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:09:13 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/03 02:11:18 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_builtin(
	int argc,
	char const *argv[])
{
	char	*path;

	if (argc == 1)
		path = getenv("HOME");
	else
		path = (char *)argv[1];
	if (chdir(path) != 0)
		return (fprintf(stderr, "cd: %s\n", path), 1);
	return (0);
}
