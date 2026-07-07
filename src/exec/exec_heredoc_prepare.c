/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_prepare.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:50:14 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/07 21:50:19 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	start_heredoc_input(int *saved_stdin)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin < 0)
		return (perror("dup"), 0);
	g_signal = 0;
	setup_heredoc_signals();
	return (1);
}

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

static int	fail_heredoc(int write_fd, char *path, int saved_stdin)
{
	close(write_fd);
	unlink(path);
	finish_heredoc_input(saved_stdin);
	return (0);
}

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