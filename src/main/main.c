/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:55 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 11:34:45 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Main function which 
1.	Silences argc & argv
2.	Initializes the shell structure
3.	Launches the main signal setup
4.	Launches the shell loop. This is necessay so minishell doesn't close 
	after one entry
*/ 

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	shell_loop(&shell);
	return (0);
}
