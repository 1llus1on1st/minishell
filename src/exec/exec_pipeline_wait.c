/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_wait.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:08:39 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 14:10:36 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Converts a signaled pipeline child status into a shell exit code.
1.	Prints the expected terminal message for SIGINT or SIGQUIT
2.	Returns 128 plus the signal number
*/
static int	pipeline_signal_status(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	return (128 + sig);
}

/*
Converts the final pipeline command status into a shell exit code.
1.	Uses the normal exit status when the command exited normally
2.	Uses signal conversion when the command died from a signal
*/
static int	pipeline_last_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (pipeline_signal_status(status));
	return (1);
}

/*
Waits for every process in a pipeline.
1.	Waits for children in the order their pids were stored
2.	Keeps the status from the last pipeline command
3.	Returns that last command status as the pipeline status
*/
int	wait_pipeline(pid_t *pids, int count)
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
			last_status = pipeline_last_status(status);
		i++;
	}
	return (last_status);
}
