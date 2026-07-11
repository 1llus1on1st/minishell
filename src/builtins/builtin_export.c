/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:13:23 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/11 13:18:25 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Prints the export invalid option error.
1.	Reports the option that caused export to fail
2.	Returns 2 because invalid options are usage errors
*/
static int	export_option_error(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putchar_fd(arg[0], 2);
	if (arg[1])
		ft_putchar_fd(arg[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (2);
}

/*
Prints the export invalid identifier error.
1.	Shows the original argument between quotes
2.	Returns 1 so export can continue checking later arguments
*/
int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

/*
Implements the export builtin.
1.	Prints sorted exports when no arguments are given
2.	Rejects option-like arguments as invalid options
3.	Handles NAME+=value with the append helper
4.	Validates normal identifiers before changing the environment
5.	Keeps processing later arguments after identifier errors
*/
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
