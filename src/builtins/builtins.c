/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:04:57 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/02 20:54:33 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_int8_t	set_builtins(
	t_minishell *msh
) {
	msh->builtins = ft_hashmap_new(4, ft_hashmap_hashstr, ft_hashmap_strcmp);
	if (msh->builtins == NULL)
		return (0);
	ft_hashmap_put(msh->builtins, ft_strdup("cd"), builtin_cd);
	ft_hashmap_put(msh->builtins, ft_strdup("echo"), builtin_echo);
	ft_hashmap_put(msh->builtins, ft_strdup("exit"), builtin_exit);
	ft_hashmap_put(msh->builtins, ft_strdup("pwd"), builtin_pwd);
	ft_hashmap_put(msh->builtins, ft_strdup("unset"), builtin_unset);
	return (1);
}

u_int8_t	is_builtin(
	const char *command_name,
	t_minishell *msh
) {
	return (ft_hashmap_contains_key(msh->builtins, command_name));
}
