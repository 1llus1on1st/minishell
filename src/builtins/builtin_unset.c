/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:13:42 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 20:00:43 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (!is_valid_identifier(cmd->argv[i], 0))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else if (!env_unset_key(shell, cmd->argv[i]))
			status = 1;
		i++;
	}
	return (status);
}
