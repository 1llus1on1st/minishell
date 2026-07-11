/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 19:34:23 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:02:08 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Connects a pipeline child's stdin to the previous pipe.
1.	The first command keeps its existing stdin
2.	Other commands read from the previous pipe read end
*/
static int	setup_input_pipe(int *pipes, int index)
{
	if (index == 0)
		return (1);
	if (dup2(pipes[(index - 1) * 2], STDIN_FILENO) < 0)
		return (perror("dup2"), 0);
	return (1);
}

/*
Connects a pipeline child's stdout to the next pipe.
1.	The last command keeps its existing stdout
2.	Other commands write to the current pipe write end
*/
static int	setup_output_pipe(int *pipes, int index, int count)
{
	if (index == count - 1)
		return (1);
	if (dup2(pipes[index * 2 + 1], STDOUT_FILENO) < 0)
		return (perror("dup2"), 0);
	return (1);
}

/*
Sets up pipe fds for one pipeline child.
1.	Connects stdin and stdout based on the child position
2.	Closes all pipe fds after dup2 so children do not keep extras open
*/
static int	setup_pipeline_fds(int *pipes, int index, int count)
{
	if (!setup_input_pipe(pipes, index))
		return (0);
	if (!setup_output_pipe(pipes, index, count))
		return (0);
	close_pipes(pipes, count);
	return (1);
}

/*
Executes one command inside a pipeline child.
1.	Applies command redirections after pipe setup
2.	Allows empty redirection-only pipeline commands to exit successfully
3.	Runs builtins in the child so they behave like pipeline commands
4.	Resolves and execs external commands
*/
static void	exec_pipeline_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	int		exit_status;

	exit_status = 0;
	if (!apply_redirections(cmd))
		exit_child(shell, 1);
	if (!cmd->argv || !cmd->argv[0])
		exit_child(shell, 0);
	if (is_builtin(cmd->argv[0]))
		exit_child(shell, execute_builtin(shell, cmd));
	path = get_cmd_path(shell, cmd->argv[0], &exit_status);
	if (!path)
		exit_child(shell, exit_status);
	execve(path, cmd->argv, shell->env);
	perror(cmd->argv[0]);
	exit_child(shell, 126);
}

/*
Entry point for a forked pipeline child.
1.	Restores default child signal behavior
2.	Sets up the pipe fds for this child's pipeline position
3.	Executes the command and exits inside the child process
*/
void	run_pipeline_child(t_shell *shell, t_cmd *cmd, int *pipes, int info[2])
{
	setup_child_signals();
	if (!setup_pipeline_fds(pipes, info[0], info[1]))
		exit_child(shell, 1);
	exec_pipeline_cmd(shell, cmd);
}
