/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:02:34 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/01 14:50:27 by mshargan         ###   ########.fr       */
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

static void	exit_numeric_error(t_shell *shell, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	exit(2);
}

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	long long	code;

	printf("exit\n");
	code = shell->last_exit;
	if (cmd->argv[1] && !parse_exit_code(cmd->argv[1], &code))
		exit_numeric_error(shell, cmd->argv[1]);
	if (argv_count(cmd->argv) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	exit((unsigned char)code);
}