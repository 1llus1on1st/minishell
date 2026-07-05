/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stdio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 18:37:56 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 19:59:21 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	save_stdio(int saved[2])
{
	saved[0] = dup(STDIN_FILENO);
	if (saved[0] < 0)
		return (perror("dup"), 0);
	saved[1] = dup(STDOUT_FILENO);
	if (saved[1] < 0)
	{
		close(saved[0]);
		return (perror("dup"), 0);
	}
	return (1);
}

int	restore_stdio(int saved[2])
{
	if (dup2(saved[0], STDIN_FILENO) < 0)
		return (perror("dup2"), 0);
	if (dup2(saved[1], STDOUT_FILENO) < 0)
		return (perror("dup2"), 0);
	close(saved[0]);
	close(saved[1]);
	return (1);
}

int	execute_redir_only(t_cmd *cmd)
{
	int	saved[2];
	int	status;

	if (!save_stdio(saved))
		return (1);
	status = 0;
	if (!apply_redirections(cmd))
		status = 1;
	if (!restore_stdio(saved))
		status = 1;
	return (status);
}

int	execute_builtin_with_redirs(t_shell *shell, t_cmd *cmd)
{
	int	saved[2];
	int	status;

	if (!cmd->redirs)
		return (execute_builtin(shell, cmd));
	if (!save_stdio(saved))
		return (1);
	if (!apply_redirections(cmd))
		status = 1;
	else
		status = execute_builtin(shell, cmd);
	if (!restore_stdio(saved))
		status = 1;
	return (status);
}
