/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:13:42 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 10:55:41 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_option_error(char *arg)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putchar_fd(arg[0], 2);
	if (arg[1])
		ft_putchar_fd(arg[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (2);
}

static int	is_valid_unset_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '-')
			return (unset_option_error(cmd->argv[i]));
		if (is_valid_unset_identifier(cmd->argv[i]))
			env_unset(shell, cmd->argv[i]);
		i++;
	}
	return (0);
}
