/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 03:42:25 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/31 14:43:43 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	init_minishell(void);

int	main(
	int argc,
	char const *argv[],
	char **envp
)
{
	t_minishell	minishell;
	char		*line;

	minishell = init_minishell();
	line = NULL;
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (EXIT_FAILURE);

	/* ====================================================================== */

	char *cmd = "/usr/bin/whoami";
	char *args[] = {"whoami", NULL};
	__pid_t	pid = fork(); // Creates a "secondary" process
	if (pid == 0)
	{
		execve(cmd, args, envp);
		exit(0);
	}
	waitpid(pid, NULL, 0); // Makes the "parent" process wait until the "child"
                           // has finished

	/* ====================================================================== */

	cmd = "/usr/bin/hostname";
	args[0] = "hostname";
	args[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, args, envp);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	read_history(minishell.history_file);
	while (1)
	{
		if (line)
			free(line);
		line = readline(minishell.prompt);
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			write_history(minishell.history_file);
			if (!ft_strncmp("exit\0", line, 5))
				break ;
			cmd = ft_strjoin("/usr/bin/", line);
			args[0] = line;
			args[1] = NULL;
			pid = fork();
			if (pid == 0)
			{
				execve(cmd, args, envp);
				exit(0);
			}
			waitpid(pid, NULL, 0);
			free(cmd);
		}
		// ft_putendl(line);
	}
	rl_clear_history();
	free(line);
	free((char *)minishell.history_file);
	ft_free_split(minishell.env.path);
	return (EXIT_SUCCESS);
}

static t_minishell	init_minishell(void)
{
	t_minishell	minishell;

	ft_bzero(&minishell, sizeof(t_minishell));
	minishell.prompt = RED_TEXT"minishell> "RESET;
	minishell.env.home = getenv("HOME");
	minishell.history_file = ft_strjoin(minishell.env.home, HISTORY_FILE);
	minishell.env.path = ft_split(getenv("PATH"), ':');
	return (minishell);
}
