/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 18:37:50 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 12:21:56 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redir_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	return (0);
}

static int	apply_read_write_redir(char *file, int target_fd)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		return (redir_error(file));
	if (dup2(fd, target_fd) < 0)
		return (close(fd), redir_error(file));
	close(fd);
	return (1);
}

static int	apply_input_redir(char *file, int target_fd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (redir_error(file));
	if (dup2(fd, target_fd) < 0)
		return (close(fd), redir_error(file));
	close(fd);
	return (1);
}

static int	apply_output_redir(char *file, int append, int target_fd)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
		return (redir_error(file));
	if (dup2(fd, target_fd) < 0)
		return (close(fd), redir_error(file));
	close(fd);
	return (1);
}

static int	apply_here_string(char *word, int target_fd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), 0);
	if (write(pipe_fd[1], word, ft_strlen(word)) < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (perror("write"), 0);
	}
	if (write(pipe_fd[1], "\n", 1) < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (perror("write"), 0);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], target_fd) < 0)
	{
		close(pipe_fd[0]);
		return (perror("dup2"), 0);
	}
	close(pipe_fd[0]);
	return (1);
}

static int	apply_one_redir(t_redir *redir)
{
	if (redir->type == T_REDIR_IN)
		return (apply_input_redir(redir->file, redir->fd));
	if (redir->type == T_REDIR_OUT)
		return (apply_output_redir(redir->file, 0, redir->fd));
	if (redir->type == T_APPEND)
		return (apply_output_redir(redir->file, 1, redir->fd));
	if (redir->type == T_READ_WRITE)
		return (apply_read_write_redir(redir->file, redir->fd));
	if (redir->type == T_HERE_STRING)
		return (apply_here_string(redir->file, redir->fd));
	if (redir->type == T_HEREDOC)
	{
		if (redir->heredoc_fd < 0)
			return (0);
		if (dup2(redir->heredoc_fd, redir->fd) < 0)
			return (perror("dup2"), 0);
		close(redir->heredoc_fd);
		redir->heredoc_fd = -1;
		return (1);
	}
	return (1);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (!apply_one_redir(redir))
			return (0);
		redir = redir->next;
	}
	return (1);
}
