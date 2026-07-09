/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_modes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:58:45 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 11:36:02 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Handles Ctrl-C while minishell is reading heredoc input.
1.	Stores the received signal in the global signal variable
2.	Writes a newline so the terminal output stays clean
3.	Closes standard input to interrupt the heredoc readline/get_next_line
4.	Lets the heredoc preparation code notice the signal afterward
*/
static void	handle_heredoc_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

/*
Sets signal behavior for the parent while child processes are running.
1.	Ignores SIGINT in the parent process during execution
2.	Ignores SIGQUIT in the parent process during execution
3.	Prevents the shell itself from reacting like the foreground child command
4.	Allows the child process signal result to be handled after wait finishes
*/
void	setup_parent_signals(void)
{
	set_signal_handler(SIGINT, SIG_IGN);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

/*
Restores default signal behavior inside child processes.
1.	Sets SIGINT back to the default operating system behavior
2.	Sets SIGQUIT back to the default operating system behavior
3.	Allows external commands to react to Ctrl-C and Ctrl-\ normally
4.	Separates child behavior from the interactive shell prompt behavior
*/
void	setup_child_signals(void)
{
	set_signal_handler(SIGINT, SIG_DFL);
	set_signal_handler(SIGQUIT, SIG_DFL);
}

/*
Sets signal behavior while minishell is reading a heredoc.
1.	Handles SIGINT with the heredoc-specific Ctrl-C handler
2.	Makes Ctrl-C interrupt heredoc input instead of only clearing a prompt line
3.	Ignores SIGQUIT so Ctrl-\ does not quit during heredoc input
4.	Lets the caller restore prompt signals after heredoc handling finishes
*/
void	setup_heredoc_signals(void)
{
	set_signal_handler(SIGINT, handle_heredoc_sigint);
	set_signal_handler(SIGQUIT, SIG_IGN);
}
