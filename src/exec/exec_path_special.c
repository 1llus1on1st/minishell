/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_special.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:06:15 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 14:06:46 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks command equality against a special command name.
*/
static int	is_exact_cmd(char *cmd, char *target)
{
	return (ft_strncmp(cmd, target, ft_strlen(target) + 1) == 0);
}

/*
Handles command names that need custom shell errors.
1.	Treats '~' as a directory-like execution error
2.	Treats '.' and '..' as command-not-found in this minishell
3.	Returns 1 when normal path lookup should continue
*/
int	handle_special_cmd_name(char *cmd, int *exit_status)
{
	if (is_exact_cmd(cmd, "~"))
	{
		ft_putstr_fd("minishell: ~: Is a directory\n", 2);
		*exit_status = 126;
		return (0);
	}
	if (is_exact_cmd(cmd, ".") || is_exact_cmd(cmd, ".."))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		*exit_status = 127;
		return (0);
	}
	return (1);
}
