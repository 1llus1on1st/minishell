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
Initializes the main shell structure before the prompt loop starts.
1.	Sets last_exit to 0 because no command has failed yet
2.	Initializes the environment and garbage collector pointers to NULL
3.	Builds the shell environment list from envp
4.	Clears shell-level allocations if environment initialization fails
5.	Exits with status 1 when minishell cannot be initialized safely
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
