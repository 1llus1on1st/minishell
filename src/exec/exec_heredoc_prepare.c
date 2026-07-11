/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_prepare.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:50:14 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 11:36:43 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Switches the shell into heredoc input mode.
1.	Saves stdin so Ctrl-C can close and later restore it
2.	Clears the global signal flag before reading heredoc lines
3.	Installs heredoc-specific signal handlers
*/
static int	start_heredoc_input(int *saved_stdin)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin < 0)
		return (perror("dup"), 0);
	g_signal = 0;
	setup_heredoc_signals();
	return (1);
}

/*
Restores normal prompt input after heredoc reading.
1.	Restores saved stdin onto STDIN_FILENO
2.	Closes the saved descriptor
3.	Reinstalls prompt signal behavior
*/
static int	finish_heredoc_input(int saved_stdin)
{
	int	status;

	status = 1;
	if (dup2(saved_stdin, STDIN_FILENO) < 0)
		status = 0;
	close(saved_stdin);
	setup_prompt_signals();
	if (!status)
		return (perror("dup2"), 0);
	return (1);
}

/*
Cleans up a failed heredoc preparation.
1.	Closes the temporary write fd
2.	Unlinks the temporary file path
3.	Restores stdin and prompt signal handling
*/
static int	fail_heredoc(int write_fd, char *path, int saved_stdin)
{
	close(write_fd);
	unlink(path);
	finish_heredoc_input(saved_stdin);
	return (0);
}

/*
Reopens the temporary heredoc file for reading.
1.	Closes the write side after heredoc content has been written
2.	Unlinks the path so the temporary file disappears after close
3.	Returns the read fd that execution will later dup onto stdin
*/
static int	open_heredoc_read(char *path, int write_fd)
{
	int	read_fd;

	close(write_fd);
	read_fd = open(path, O_RDONLY);
	unlink(path);
	if (read_fd < 0)
		return (perror(path), -1);
	return (read_fd);
}

/*
Prepares one heredoc redirection for later execution.
1.	Creates a unique temporary heredoc file
2.	Reads user input with heredoc signal behavior enabled
3.	Restores stdin and prompt signals after input is finished
4.	Stores the reopened read fd on the redirection node
*/
int	prepare_one_heredoc(t_shell *shell, t_redir *redir)
{
	char	*path;
	int		write_fd;
	int		read_fd;
	int		saved_stdin;

	path = NULL;
	write_fd = open_unique_heredoc(shell, &path);
	if (write_fd < 0)
		return (0);
	if (!start_heredoc_input(&saved_stdin))
		return (close(write_fd), unlink(path), 0);
	if (!read_heredoc_loop(shell, redir, write_fd))
		return (fail_heredoc(write_fd, path, saved_stdin));
	if (!finish_heredoc_input(saved_stdin))
		return (close(write_fd), unlink(path), 0);
	read_fd = open_heredoc_read(path, write_fd);
	if (read_fd < 0)
		return (0);
	if (redir->heredoc_fd >= 0)
		close(redir->heredoc_fd);
	redir->heredoc_fd = read_fd;
	return (1);
}
