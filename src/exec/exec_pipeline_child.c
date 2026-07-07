/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 19:34:23 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/07 21:43:22 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	setup_input_pipe(int *pipes, int index)
{
	if (index == 0)
		return (1);
	if (dup2(pipes[(index - 1) * 2], STDIN_FILENO) < 0)
		return (perror("dup2"), 0);
	return (1);
}

static int	setup_output_pipe(int *pipes, int index, int count)
{
	if (index == count - 1)
		return (1);
	if (dup2(pipes[index * 2 + 1], STDOUT_FILENO) < 0)
		return (perror("dup2"), 0);
	return (1);
}

static int	setup_pipeline_fds(int *pipes, int index, int count)
{
	if (!setup_input_pipe(pipes, index))
		return (0);
	if (!setup_output_pipe(pipes, index, count))
		return (0);
	close_pipes(pipes, count);
	return (1);
}

static void	exec_pipeline_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	int		exit_status;

	exit_status = 0;
	if (!apply_redirections(cmd))
		exit(1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(shell, cmd));
	path = get_cmd_path(shell, cmd->argv[0], &exit_status);
	if (!path)
		exit(exit_status);
	execve(path, cmd->argv, shell->env);
	perror(cmd->argv[0]);
	exit(126);
}

void	run_pipeline_child(t_shell *shell, t_cmd *cmd, int *pipes, int info[2])
{
	setup_child_signals();
	if (!setup_pipeline_fds(pipes, info[0], info[1]))
		exit(1);
	exec_pipeline_cmd(shell, cmd);
}
