/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:02:27 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 10:47:01 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Implements the env builtin without external command support.
1.	Rejects extra arguments because this minishell does not run env commands
2.	Prints only entries that contain '='
3.	Hides export-only names that have no value assigned
*/
int	builtin_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (cmd->argv[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	i = 0;
	while (shell->env && shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
