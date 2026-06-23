/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:02:34 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/23 14:30:53 by mshargan         ###   ########.fr       */
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

static int	is_space_char(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space_char(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !is_space_char(str[i]))
			return (0);
		i++;
	}
	return (1);
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
	int	code;

	printf("exit\n");
	if (cmd->argv[1] && !is_numeric_arg(cmd->argv[1]))
		exit_numeric_error(shell, cmd->argv[1]);
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
	exit((unsigned char)code);
}