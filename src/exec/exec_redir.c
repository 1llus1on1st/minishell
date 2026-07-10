/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 18:37:50 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:36:57 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	apply_heredoc_redir(t_redir *redir)
{
	if (redir->heredoc_fd < 0)
		return (0);
	if (dup2(redir->heredoc_fd, redir->fd) < 0)
		return (perror("dup2"), 0);
	close(redir->heredoc_fd);
	redir->heredoc_fd = -1;
	return (1);
}

static int	apply_one_redir(t_redir *redir)
{
	if (redir->fd < 0)
		return (ft_putstr_fd("minishell: bad file descriptor\n", 2), 0);
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
		return (apply_heredoc_redir(redir));
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
