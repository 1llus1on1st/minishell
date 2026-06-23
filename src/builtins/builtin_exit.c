/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:02:34 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/23 14:03:55 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	argv_count(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	int	code;

	printf("exit\n");
	if (argv_count(cmd->argv) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	code = shell->last_exit;
	if (cmd->argv[1])
		code = ft_atoi(cmd->argv[1]);
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	exit(code);
}