/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:27:27 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/06 09:27:28 by mshargan         ###   ########.fr       */
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
	write(fd, out, ft_strlen(out));
	write(fd, "\n", 1);
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

static int	prepare_one_heredoc(t_shell *shell, t_redir *redir)
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (perror("pipe"), 0);
	if (!read_heredoc_loop(shell, redir, fd[1]))
		return (close(fd[0]), close(fd[1]), 0);
	close(fd[1]);
	if (redir->heredoc_fd >= 0)
		close(redir->heredoc_fd);
	redir->heredoc_fd = fd[0];
	return (1);
}

void	close_heredoc_fds(t_cmd *cmds)
{
	t_redir	*redir;

	while (cmds)
	{
		redir = cmds->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC && redir->heredoc_fd >= 0)
				close(redir->heredoc_fd);
			redir = redir->next;
		}
		cmds = cmds->next;
	}
}

int	prepare_heredocs(t_shell *shell, t_cmd *cmds)
{
	t_redir	*redir;

	while (cmds)
	{
		redir = cmds->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				if (!prepare_one_heredoc(shell, redir))
					return (0);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (1);
}