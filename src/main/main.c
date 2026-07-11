/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:55 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/11 12:39:05 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Starts minishell and keeps it running through the main shell loop.
1.	Silences argc and argv because minishell does not use program arguments
2.	Initializes the shell structure with the inherited environment
3.	Sets the prompt signal behavior before reading user input
4.	Launches shell_loop so minishell keeps accepting commands
5.	Returns 0 only if the shell loop ever finishes normally
*/
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_prompt_signals();
	shell_loop(&shell);
	return (0);
}
