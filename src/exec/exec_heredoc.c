/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:27:27 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/07 21:34:28 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Closes any heredoc read fds still stored on command redirections.
1.	Walks every command and every redirection
2.	Closes only heredoc descriptors that are currently open
3.	Resets heredoc_fd to -1 to avoid double-closing later
*/
void	close_heredoc_fds(t_cmd *cmds)
{
	t_redir	*redir;

	while (cmds)
	{
		redir = cmds->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC && redir->heredoc_fd >= 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
}

/*
Prepares all heredocs before command execution starts.
1.	Reads heredocs from left to right across the full command list
2.	Stores each prepared heredoc as a read fd on its redirection node
3.	Stops immediately if a heredoc is interrupted or cannot be prepared
*/
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
