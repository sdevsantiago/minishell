/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 03:42:25 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/04 00:29:45 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	init_minishell(char **envp);
static void	minishell(t_minishell *minishell, char **envp);
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

	(void)argv;
	errno = 0;
	if (argc != 1)
		return (errno = EINVAL, errno);
	shell = init_minishell(envp);
	minishell(&shell, envp);
	clear_minishell(&shell);
	return (EXIT_SUCCESS);
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

	ft_bzero(&minishell, sizeof(t_minishell));
	minishell.history_file = ft_strjoin(getenv("HOME"), HISTORY_FILE);
	// minishell.path = ft_split(getenv("PATH"), ':');
	minishell.envp = envp;
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
static void	minishell(t_minishell *minishell, char **envp)
{
	char	*line;
	char 	*cmd;
	char 	*args[2];
	pid_t	pid;

	line = NULL;
	read_history(minishell->history_file);
	while (1)
	{
		if (line)
			free(line);
		char	*prompt;
		char	*hostname = get_hostname();
		if (hostname)
		{
			prompt = ft_strjoin_mul(12,
				BOLD, BLUE_TEXT, getenv("USER"), "@", hostname,
				RESET, ":",
				BOLD, GREEN_TEXT, getenv("PWD"),
				RESET, "> ");
			free(hostname);
		}
		if (prompt)
		{
			line = readline(prompt);
			free(prompt);
		}
		else
			line = readline("minishell> ");
		if (!line && exit_builtin(1, NULL))
			break ;
		if (*line)
		{
			add_history(line);
			write_history(minishell->history_file);

			t_cmd cmd_parse = parse_cmd(line, minishell);
			// exec_cmd();

			// builtins
			if (ft_strncmp("exit\0", line, 5) == 0 && exit_builtin(1, NULL) != -1)
				break ;
			else if (ft_strncmp("cd\0", line, 3) == 0)
				cd_builtin(1, NULL);
			else if (ft_strncmp("pwd\0", line, 4) == 0)
				pwd_builtin(1, NULL);
			else if (ft_strncmp("env\0", line, 4) == 0)
				env_builtin(1, NULL);
			else if (ft_strncmp("echo\0", line, 5) == 0)
				echo_builtin(0, NULL);
			// not builtins
			else
			{
				// if string does not start with "./"
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
		}
	}
	rl_clear_history();
	free(line);
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
	// ft_free_split(minishell->path);
	ft_bzero(minishell, sizeof(t_minishell));
}
