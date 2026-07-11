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

/*
Saves the current stdin and stdout file descriptors.
1.	Used before running parent-side builtins with redirections
2.	Allows minishell to restore the prompt's stdio afterward
*/
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

/*
Restores stdin and stdout from saved descriptors.
1.	Duplicates the saved descriptors back onto standard fds
2.	Closes the saved copies after restoration
*/
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

/*
Executes a command line that contains only redirections.
1.	Saves stdio because redirections are applied in the parent
2.	Applies redirections to test their side effects and errors
3.	Restores stdio before returning to the prompt
*/
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

/*
Executes a builtin while respecting its redirections.
1.	Runs directly when there are no redirections
2.	Saves parent stdio before applying builtin redirections
3.	Restores stdio so the shell prompt is not permanently redirected
*/
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
