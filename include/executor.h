/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:08:33 by sede-san          #+#    #+#             */
/*   Updated: 2026/02/08 21:32:56 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "core.h"
# include <stdint.h>

# define READ_PIPE 0
# define WRITE_PIPE 1
# define PIPE_ERROR -1
# define FORK_ERROR -1

typedef struct s_pipeline
{
	int	prev_read_fd;
	int	pipefd[2];
}	t_pipeline;

typedef struct s_exec_state
{
	uint8_t		exit_status;
	t_pipeline	pipeline;
	t_list		*current_command;
	pid_t		last_child_pid;
}	t_exec_state;

extern uint8_t	execute(t_list *command, t_minishell *minishell);
extern uint8_t	executor_execute_command(t_command *cmd, t_minishell *msh);
extern char		*executor_resolve_command_path(const t_command *cmd,
					t_minishell *msh);
extern bool		executor_is_builtin_command(const t_command *cmd,
					t_minishell *msh);
extern int		executor_create_pipe_if_needed(t_list *node, t_pipeline *pl);
extern bool		executor_is_fork_required(t_list *node, const t_pipeline *pl,
					t_minishell *msh);
extern void		executor_setup_child_input(t_pipeline *pipeline);
extern void		executor_setup_child_output(t_list *node, t_pipeline *pl);
extern void		executor_child_process(t_list *node, t_pipeline *pl,
					t_minishell *msh);
extern void		executor_parent_cleanup(t_list *node, t_pipeline *pl);
extern uint8_t	executor_wait_for_children(pid_t last_child_pid);
extern void		executor_cmdfree(t_command *command);
extern bool		executor_apply_redirections(const t_command *command,
					int *saved_stdin, int *saved_stdout, int *saved_stderr);
extern void		executor_restore_redirections(int saved_stdin,
					int saved_stdout, int saved_stderr);
extern bool		executor_prepare_heredocs(t_list *command_list,
					t_minishell *minishell, uint8_t *exit_status);
extern char		*executor_expand_heredoc_line(const char *line,
					t_minishell *minishell);

#endif /* EXECUTOR_H */
