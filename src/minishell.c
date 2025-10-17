/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 03:42:25 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/21 17:31:52 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	init_minishell(char **envp);
static int	minishell(t_minishell *minishell);
static void	clear_minishell(t_minishell *minishell);

/**
 * @brief Entry point for the minishell program.
 *
 * Validates the number of command-line arguments, initializes the minishell
 * structure, starts the main shell loop, and performs necessary cleanup before
 * exiting.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param envp Array of environment variable strings.
 *
 * @return int Returns EXIT_SUCCESS if the program completes successfully, or
 *             an error code on failure.
 */
int	main(
	int argc,
	char const *argv[],
	char **envp)
{
	t_minishell	shell;
	int			exit_code;

	(void)argv;
	errno = 0;
	if (argc != 1)
		return (errno = EINVAL, errno);
	init_signal();
	shell = init_minishell(envp);
	if (errno)
		fprintf(stderr, "minishell: %s\n" , strerror(errno));
	exit_code = minishell(&shell);
	clear_minishell(&shell);
	return (exit_code);
}

/**
 * @brief Initializes and returns a t_minishell structure with default values.
 *
 * This function zeroes out a t_minishell struct, sets up the history file path
 * by joining the HOME environment variable with HISTORY_FILE, and splits the
 * PATH environment variable into an array of strings using ':' as the
 * delimiter.
 *
 * @return t_minishell The initialized minishell structure.
 */
static t_minishell	init_minishell(
	char **envp)
{
	t_minishell	minishell;
	size_t		n_env;

	ft_bzero(&minishell, sizeof(t_minishell));
	n_env = 0;
	while (envp[n_env])
		n_env++;
	minishell.envp = (char **)malloc(n_env * sizeof(char *));
	if (!minishell.envp && errno == ENOMEM)
		return (clear_minishell(&minishell), minishell);
	return (minishell);
}

/**
 * @brief Main loop for the minishell program.
 *
 * This function implements the main interactive loop of the minishell. It
 * displays a dynamic prompt showing the user, hostname, and current working
 * directory, reads user input, adds commands to the history, and executes
 * commands by forking a new process. The loop continues until the user enters
 * "exit" or EOF is encountered.
 *
 * @param minishell Pointer to the minishell state structure, containing at
 *                  least the history file path.
 * @param envp      Environment variables to be passed to executed commands.
 *
 * The function performs the following steps:
 *  - Loads command history from the specified history file.
 *  - Constructs and displays a prompt with user, hostname, and current
 *    directory.
 *  - Reads a line of input from the user.
 *  - If the input is not empty:
 *      - Adds the command to the history and writes it to the history file.
 *      - If the command is "exit", breaks the loop and exits.
 *      - Otherwise, constructs the command path, forks a child process, and
 *        executes the command using execve.
 *      - Waits for the child process to finish.
 *  - Cleans up allocated memory and clears the history on exit.
 */
static int	minishell(t_minishell *minishell)
{
	int		exit_code;
	char	*line;
	t_cmd	cmd;

	exit_code = 0;
	line = NULL;
	// read_history(minishell->history_file);
	while (1)
	{
		if (line)
			free(line);
		char	*prompt = NULL;
		char	*hostname = get_hostname();
		if (hostname)
		{
			free(hostname);
		}
		if (prompt)
		{
			line = readline(prompt);
			free(prompt);
		}
		else
			line = readline("minishell> ");
		if (!line)
		{
			write_history(minishell->history_file);
			cmd = parse_cmd("exit", minishell);
			exit_code = exit_builtin(cmd.argc, (const char **)cmd.argv);
			if (exit_code != -1)
				break ;
		}
		if (*line)
		{
			add_history(line);
			cmd = parse_cmd(line, minishell);
			free(line);
			line = NULL;
			if (ft_strncmp(cmd.argv[0], "exit\0", 5) == 0)
			{
				exit_code = exit_builtin(cmd.argc, (const char **)cmd.argv);
				write_history(minishell->history_file);
				if (exit_code != -1)
					break ;
			}
			else if (is_builtin(&cmd))
				exec_builtin(&cmd, minishell->envp);
			else
				exec_cmd(&cmd, minishell->envp);
		}
	}

	write_history(minishell->history_file);
	rl_clear_history();
	if (line)
		free(line);
	return (exit_code);
}

/**
 * @brief Clears and frees resources associated with a t_minishell instance.
 *
 * This function performs the following actions:
 * - Zeroes out the contents of the history_file string.
 * - Frees the memory allocated for the history_file.
 * - Frees the memory allocated for the path array using ft_free_split.
 * - Zeroes out the entire t_minishell structure.
 *
 * @param minishell Pointer to the t_minishell structure to be cleared and
 *                  freed.
 */
static void	clear_minishell(
	t_minishell *minishell
)
{
	ft_bzero(minishell->history_file,
		ft_strlen(minishell->history_file) * sizeof(char));
	free(minishell->history_file);
	ft_bzero(minishell, sizeof(t_minishell));
}
