/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:13:47 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 15:30:39 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Writes one heredoc line to the temporary file.
1.	Expands variables when the delimiter allows heredoc expansion
2.	Writes the line content followed by a newline
*/
static int	write_heredoc_line(t_shell *shell, char *line, int fd, int expand)
{
	char	*out;

	out = line;
	if (expand)
	{
		out = expand_heredoc_line(shell, line);
		if (!out)
			return (0);
	}
	if (write(fd, out, ft_strlen(out)) < 0)
		return (perror("write"), 0);
	if (write(fd, "\n", 1) < 0)
		return (perror("write"), 0);
	return (1);
}

/*
Reads heredoc input until the delimiter, EOF or interruption.
1.	Prompts with "> " for each heredoc line
2.	Stops successfully when the line exactly matches the delimiter
3.	Reports a warning when EOF arrives before the delimiter
4.	Returns 0 when SIGINT interrupts heredoc input
*/
int	read_heredoc_loop(t_shell *shell, t_redir *redir, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal == SIGINT)
				return (0);
			ft_putstr_fd("minishell: warning: here-document delimited by "
				"end-of-file", 2);
			ft_putstr_fd(" (wanted `", 2);
			ft_putstr_fd(redir->file, 2);
			ft_putstr_fd("')\n", 2);
			return (1);
		}
		if (ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1) == 0)
			return (free(line), 1);
		if (!write_heredoc_line(shell, line, fd, redir->heredoc_expand))
			return (free(line), 0);
		free(line);
	}
}

/*
Builds a temporary heredoc path from the process id and a counter.
1.	Uses the pid to reduce collisions between minishell processes
2.	Uses count to retry if a path already exists
*/
static char	*join_heredoc_path(char *pid, int count)
{
	char	*num;
	char	*base;
	char	*tmp;
	char	*path;

	num = ft_itoa(count);
	if (!num)
		return (NULL);
	base = ft_strjoin("/tmp/minishell_hd_", pid);
	if (!base)
		return (free(num), NULL);
	tmp = ft_strjoin(base, "_");
	free(base);
	if (!tmp)
		return (free(num), NULL);
	path = ft_strjoin(tmp, num);
	free(tmp);
	free(num);
	return (path);
}

/*
Tracks a heredoc temp path after its file has been opened.
1.	Adds the path to line_gc so cleanup can free the string
2.	Closes and unlinks the file if tracking fails
*/
static int	save_heredoc_path(t_shell *shell, char **path, int fd)
{
	if (gc_add(&shell->line_gc, *path))
		return (fd);
	close(fd);
	unlink(*path);
	free(*path);
	*path = NULL;
	return (-1);
}

/*
Opens a unique temporary file for heredoc content.
1.	Builds candidate paths using pid and an increasing counter
2.	Uses O_EXCL so an existing file is never overwritten
3.	Retries only when the candidate path already exists
*/
int	open_unique_heredoc(t_shell *shell, char **path)
{
	char	*pid;
	int		fd;
	int		count;
	int		error;

	pid = ft_itoa(getpid());
	if (!pid)
		return (-1);
	count = 0;
	while (1)
	{
		*path = join_heredoc_path(pid, count);
		if (!*path)
			return (free(pid), -1);
		fd = open(*path, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
			return (free(pid), save_heredoc_path(shell, path, fd));
		error = errno;
		free(*path);
		*path = NULL;
		if (error != EEXIST)
			return (free(pid), errno = error, perror("minishell: heredoc"), -1);
		count++;
	}
}
