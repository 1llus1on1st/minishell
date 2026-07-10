/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:13:23 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:39:35 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_option_error(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putchar_fd(arg[0], 2);
	if (arg[1])
		ft_putchar_fd(arg[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (2);
}

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	status;

	if (!cmd->argv[1])
		return (print_export(shell));
	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '-')
			return (export_option_error(cmd->argv[i]));
		if (is_append_assignment(cmd->argv[i]))
		{
			if (export_append(shell, cmd->argv[i]) != 0)
				status = 1;
		}
		else if (!is_valid_identifier(cmd->argv[i], 1))
			status = export_error(cmd->argv[i]);
		else if (!env_set_entry(shell, cmd->argv[i]))
			status = 1;
		i++;
	}
	return (status);
}
