/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:42:04 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/02 20:45:53 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

u_int8_t	builtin_unset(
	t_command cmd,
	t_minishell *msh
) {
	free(ft_hashmap_remove(msh->variables.environment, cmd.argv[1]));
	return (1);
}
