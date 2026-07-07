/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 17:34:30 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/07 21:41:03 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	wait_status_to_exit(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		return (128 + sig);
	}
	return (1);
}

int	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->next)
		return (execute_pipeline(shell, cmd));
	if (!cmd->argv || !cmd->argv[0])
		return (execute_redir_only(cmd));
	if (is_builtin(cmd->argv[0]))
		return (execute_builtin_with_redirs(shell, cmd));
	return (execute_external(shell, cmd));
}

static void	run_child(t_shell *shell, t_cmd *cmd)
{
	int		exit_status;
	char	*path;

	setup_child_signals();
	exit_status = 0;
	if (!apply_redirections(cmd))
		exit(1);
	path = get_cmd_path(shell, cmd->argv[0], &exit_status);
	if (!path)
		exit(exit_status);
	execve(path, cmd->argv, shell->env);
	perror(cmd->argv[0]);
	exit(126);
}

int	execute_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		run_child(shell, cmd);
	setup_parent_signals();
	if (waitpid(pid, &status, 0) < 0)
	{
		setup_prompt_signals();
		return (perror("waitpid"), 1);
	}
	setup_prompt_signals();
	return (wait_status_to_exit(status));
}
