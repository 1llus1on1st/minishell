/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:59:16 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 10:46:48 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks whether a command name is implemented as a builtin.
1.	Returns false for NULL command names
2.	Matches exactly against the builtin names supported by minishell
*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

/*
Dispatches a command to the matching builtin implementation.
1.	Calls builtins that need shell state with the t_shell pointer
2.	Calls simple output-only builtins with just the command data
3.	Returns the builtin exit status to the executor
*/
int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (builtin_export(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (builtin_unset(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (builtin_env(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (builtin_exit(shell, cmd));
	return (1);
}
