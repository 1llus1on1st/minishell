/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:13:47 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/07 21:13:51 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	read_heredoc_loop(t_shell *shell, t_redir *redir, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (1);
		if (ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1) == 0)
			return (free(line), 1);
		if (!write_heredoc_line(shell, line, fd, redir->heredoc_expand))
			return (free(line), 0);
		free(line);
	}
}

static char	*make_heredoc_path(t_shell *shell)
{
	static int	count;
	char		*pid;
	char		*num;
	char		*tmp;
	char		*path;

	pid = ft_itoa(getpid());
	num = ft_itoa(count++);
	if (!pid || !num)
		return (free(pid), free(num), NULL);
	tmp = ft_strjoin("/tmp/minishell_hd_", pid);
	free(pid);
	if (!tmp)
		return (free(num), NULL);
	path = ft_strjoin(tmp, num);
	free(tmp);
	free(num);
	if (!path)
		return (NULL);
	if (!gc_add(&shell->line_gc, path))
		return (free(path), NULL);
	return (path);
}

static int	reopen_heredoc_file(char *path, int write_fd)
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

	path = make_heredoc_path(shell);
	if (!path)
		return (0);
	write_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write_fd < 0)
		return (perror(path), 0);
	if (!read_heredoc_loop(shell, redir, write_fd))
		return (close(write_fd), unlink(path), 0);
	read_fd = reopen_heredoc_file(path, write_fd);
	if (read_fd < 0)
		return (0);
	if (redir->heredoc_fd >= 0)
		close(redir->heredoc_fd);
	redir->heredoc_fd = read_fd;
	return (1);
}