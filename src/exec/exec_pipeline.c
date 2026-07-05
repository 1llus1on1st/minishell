/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 19:34:32 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 19:37:31 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	wait_pipeline(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 1;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) < 0)
			return (perror("waitpid"), 1);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmds)
{
	int		count;
	int		i;
	int		*pipes;
	pid_t	*pids;

	count = count_cmds(cmds);
	pipes = gc_malloc(&shell->line_gc, sizeof(int) * 2 * (count - 1));
	pids = gc_malloc(&shell->line_gc, sizeof(pid_t) * count);
	if (!pipes || !pids || !create_pipes(pipes, count))
		return (1);
	i = 0;
	while (i < count)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (close_pipes(pipes, count), perror("fork"), 1);
		if (pids[i] == 0)
			run_pipeline_child(shell, cmds, pipes, (int [2]){i, count});
		cmds = cmds->next;
		i++;
	}
	close_pipes(pipes, count);
	return (wait_pipeline(pids, count));
}