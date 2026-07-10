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

static int	pipeline_last_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (pipeline_signal_status(status));
	return (1);
}

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
