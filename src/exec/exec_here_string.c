/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:33:50 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:37:23 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_pipe_fds(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static int	write_here_string(int pipe_fd[2], char *word)
{
	if (write(pipe_fd[1], word, ft_strlen(word)) < 0)
	{
		close_pipe_fds(pipe_fd);
		return (perror("write"), 0);
	}
	if (write(pipe_fd[1], "\n", 1) < 0)
	{
		close_pipe_fds(pipe_fd);
		return (perror("write"), 0);
	}
	return (1);
}

int	apply_here_string(char *word, int target_fd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), 0);
	if (!write_here_string(pipe_fd, word))
		return (0);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], target_fd) < 0)
	{
		close(pipe_fd[0]);
		return (perror("dup2"), 0);
	}
	close(pipe_fd[0]);
	return (1);
}
