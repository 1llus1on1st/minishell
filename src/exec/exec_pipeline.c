/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 19:34:32 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 15:24:44 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Counts how many commands are in a pipeline list.
*/
static int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

/*
Creates all pipes needed for a pipeline.
1.	A pipeline with N commands needs N - 1 pipes
2.	Stores read and write fds consecutively in the pipes array
*/
static int	create_pipes(int *pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (pipe(&pipes[i * 2]) < 0)
			return (perror("pipe"), 0);
		i++;
	}
	return (1);
}

/*
Closes every pipe fd stored in the pipeline fd array.
*/
void	close_pipes(int *pipes, int count)
{
	int	i;

	i = 0;
	while (i < (count - 1) * 2)
	{
		close(pipes[i]);
		i++;
	}
}

/*
Forks every child process in a pipeline.
1.	Stores each child pid so the parent can wait later
2.	Runs pipeline setup and execution in the child branch
3.	Cleans up already-created children if a later fork fails
*/
static int	fork_pipeline(t_shell *shell, t_cmd *cmds, int *pipes,
		pid_t *pids)
{
	int	i;
	int	count;

	i = 0;
	count = count_cmds(cmds);
	while (i < count)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork");
			close_pipes(pipes, count);
			wait_pipeline(pids, i);
			return (0);
		}
		if (pids[i] == 0)
			run_pipeline_child(shell, cmds, pipes, (int [2]){i, count});
		cmds = cmds->next;
		i++;
	}
	return (1);
}

/*
Executes a multi-command pipeline.
1.	Allocates the pipe and pid arrays for the full pipeline
2.	Creates all pipes before forking children
3.	Ignores prompt signals in the parent while children run
4.	Closes parent pipe fds and returns the last command's status
*/
int	execute_pipeline(t_shell *shell, t_cmd *cmds)
{
	int		count;
	int		*pipes;
	pid_t	*pids;
	int		status;

	count = count_cmds(cmds);
	pipes = gc_malloc(&shell->line_gc, sizeof(int) * 2 * (count - 1));
	pids = gc_malloc(&shell->line_gc, sizeof(pid_t) * count);
	if (!pipes || !pids || !create_pipes(pipes, count))
		return (1);
	setup_parent_signals();
	if (!fork_pipeline(shell, cmds, pipes, pids))
	{
		setup_prompt_signals();
		return (1);
	}
	close_pipes(pipes, count);
	status = wait_pipeline(pids, count);
	setup_prompt_signals();
	return (status);
}
