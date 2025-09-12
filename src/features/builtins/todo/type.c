/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:12:49 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/20 22:27:32 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_builtin(
	int argc,
	char const *argv[])
{
	int	exit_code;

	if (is_builtin((t_cmd*){argc, argv}))
	{
		printf("%s is a shell builtin\n", argv[0]);
		exit_code = 0;
	}
	return (exit_code);
}
