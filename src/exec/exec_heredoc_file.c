/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:13:47 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 12:18:27 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_piped_line(void)
{
	char	*line;
	char	*new_line;
	size_t	len;
	ssize_t	bytes;
	char	c;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	len = 0;
	while (1)
	{
		bytes = read(STDIN_FILENO, &c, 1);
		if (bytes <= 0 || c == '\n')
			break ;
		new_line = malloc(len + 2);
		if (!new_line)
			return (free(line), NULL);
		ft_memcpy(new_line, line, len);
		new_line[len] = c;
		new_line[len + 1] = '\0';
		free(line);
		line = new_line;
		len++;
	}
	if (bytes <= 0 && len == 0)
		return (free(line), NULL);
	return (line);
}

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

int	read_heredoc_loop(t_shell *shell, t_redir *redir, int fd)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = read_piped_line();
		if (!line)
		{
			if (g_signal == SIGINT)
				return (0);
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file", 2);
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

static char	*join_heredoc_path(t_shell *shell, char *pid, int count)
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
	if (!path)
		return (NULL);
	if (!gc_add(&shell->line_gc, path))
		return (free(path), NULL);
	return (path);
}

int	open_unique_heredoc(t_shell *shell, char **path)
{
	char	*pid;
	int		fd;
	int		count;

	pid = ft_itoa(getpid());
	if (!pid)
		return (-1);
	count = 0;
	while (count < 1000)
	{
		*path = join_heredoc_path(shell, pid, count++);
		if (!*path)
			return (free(pid), -1);
		fd = open(*path, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
			return (free(pid), fd);
	}
	free(pid);
	ft_putstr_fd("minishell: heredoc temp file error\n", 2);
	return (-1);
}
