/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:13:42 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/23 14:13:48 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	(void)shell;
	(void)cmd;
	ft_putstr_fd("unset: not implemented yet\n", 2);
	return (1);
}