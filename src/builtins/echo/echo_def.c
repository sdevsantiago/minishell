/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_def.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:06:30 by sede-san          #+#    #+#             */
/*   Updated: 2025/11/02 03:11:01 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo_def.h"

static void		assign_flags(t_args *args, t_command cmd, size_t *i);
static u_int8_t	is_valid_flag(t_args *args, char *flag);

static void	assign_default_flags(
	t_args *args
){
	args->no_newline = (t_arg){
		.short_name = 'n', .long_name = NULL,
		.data = {.b = false}
	};
}

t_args	read_args(
	t_command cmd
){
	t_args	args;
	size_t	i;

	assign_default_flags(&args);
	i = 0;
	assign_flags(&args, cmd, &i);
	args.strings.data.sp = &cmd.argv[i];
	return (args);
}

static void	assign_flags(
	t_args *args,
	t_command cmd,
	size_t *i
){
	while (cmd.argv[++(*i)] && ft_strchr(cmd.argv[*i], '-'))
	{
		if (!is_valid_flag(args, cmd.argv[*i]))
			break ;
		else
			args->no_newline.data.b = true;
	}
}

static u_int8_t	is_valid_flag(
	t_args *args,
	char *flag
){
	size_t	i;

	if (!flag[1])
		return (0);
	i = 0;
	while (flag[++i])
	{
		if (flag[i] != args->no_newline.short_name)
			return (0);
	}
	return (1);
}
