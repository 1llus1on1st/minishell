/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 17:34:30 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 17:47:33 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	wait_status_to_exit(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd->argv[0]))
		return (execute_builtin(shell, cmd));
	return (execute_external(shell, cmd));
}

int	execute_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		exit_status;
	char	*path;

	exit_status = 0;
	path = get_cmd_path(shell, cmd->argv[0], &exit_status);
	if (!path)
		return (exit_status);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		execve(path, cmd->argv, shell->env);
		perror(cmd->argv[0]);
		exit(126);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid"), 1);
	return (wait_status_to_exit(status));
}
