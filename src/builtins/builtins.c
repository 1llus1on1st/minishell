/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:59:16 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 20:00:47 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (builtin_env(shell));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (builtin_exit(shell, cmd));
	return (1);
}
