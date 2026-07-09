/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:59 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 11:42:23 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
1.	Initializes the values of the variables in the t_shell structure
2.	Launches the initializer of the garbage collector
	If it fails launches the clear of the garbage collector which can contain 
	partial t_shell data
*/
void	init_shell(t_shell *shell, char **envp)
{
	shell->last_exit = 0;
	shell->env = NULL;
	shell->line_gc = NULL;
	shell->shell_gc = NULL;
	if (!init_env(shell, envp))
	{
		gc_clear(&shell->shell_gc);
		exit(1);
	}
}
