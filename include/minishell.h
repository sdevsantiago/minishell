/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:35:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/10/20 20:20:30 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>	// readline(3), rl_clear_history(),
								// rl_on_new_line(), rl_replace_line(),
								// rl_redisplay()
# include <readline/history.h>	// add_history()
# include <stdio.h>				// printf(3), perror(3)
# include <stdlib.h>			// malloc(3), free(3), exit(3), getenv(3)
# include <unistd.h>			// write(2), getcwd(3), chdir(2), unlink(2),
								// execve(2), dup(2), dup2(2), pipe(2),
								// isatty(3), ttyname(3), ttyslot(3)
# include <fcntl.h>				// open(2)
# include <sys/wait.h>			// wait(2), waitpid(2), wait3(2), wait4(2)
# include <signal.h>			// signal(2), sigaction(2), sigemptyset(3),
								// sigaddset(3), kill(2)
# include <sys/stat.h>			// stat(2), lstat(2), fstat(2)
# include <sys/types.h>			// opendir(3), closedir(3)
# include <dirent.h>			// opendir(3), readdir(3), closedir(3)
# include <string.h>			// strerror(3)
# include <sys/ioctl.h>			// ioctl(2)
# include <termios.h>			// tcsetattr(3), tcgetattr(3)
# include <term.h>				// tgetent(3), tgetflag(3), tgetnum(3),
								// tgetstr(3), tgoto(3), tputs(3)

#endif /* MINISHELL_H */
