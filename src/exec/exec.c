/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 17:34:30 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 17:57:22 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Converts a waitpid status into a shell exit status.
1.	Returns the child exit code when the process exited normally
2.	Prints the expected terminal message for SIGINT and SIGQUIT
3.	Returns 128 + signal number for signaled children
*/
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

/*
Chooses how to execute one parsed command list.
1.	Runs pipelines through the pipeline executor
2.	Applies redirections even when there is no command name
3.	Runs builtins in the parent when possible so shell state can change
4.	Forks only for external commands
*/
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

/*
Runs an external command inside a forked child process.
1.	Restores default child signal behavior
2.	Applies redirections before resolving the executable path
3.	Exits with the correct shell status when lookup or execve fails
*/
static void	run_child(t_shell *shell, t_cmd *cmd)
{
	int		exit_status;
	char	*path;

	setup_child_signals();
	exit_status = 0;
	if (!apply_redirections(cmd))
		exit_child(shell, 1);
	path = get_cmd_path(shell, cmd->argv[0], &exit_status);
	if (!path)
		exit_child(shell, exit_status);
	execve(path, cmd->argv, shell->env);
	perror(cmd->argv[0]);
	exit_child(shell, 126);
}

/*
Executes a single non-builtin command.
1.	Forks so execve cannot replace the minishell process
2.	Ignores prompt signals in the parent while the child runs
3.	Waits for the child and converts its wait status into last_exit form
*/
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
