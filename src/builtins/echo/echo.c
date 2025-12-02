/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 02:41:11 by sede-san          #+#    #+#             */
/*   Updated: 2025/12/01 18:05:51 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "echo_def.h"

u_int8_t	builtin_echo(
	t_command cmd,
	t_minishell *msh
){
	const t_args	args = read_args(cmd);
	size_t			i;

	(void)msh;
	i = -1;
	while (args.strings.data.sp[++i])
	{
		ft_putstr(args.strings.data.sp[i]);
		if (args.strings.data.sp[i + 1])
			ft_putchar(SPACE);
	}
	if (args.no_newline.data.b == false)
		ft_putchar(NEWLINE);
	return (EXIT_SUCCESS);
}
