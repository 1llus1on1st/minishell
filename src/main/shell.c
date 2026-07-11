/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:14:25 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/11 12:46:44 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Reads one line from the user prompt.
1.	Displays the minishell prompt using readline
2.	Returns NULL when readline receives EOF, usually from Ctrl-D
3.	Adds non-empty input lines to the readline history
4.	Does not add empty lines
5.	Returns the allocated input line
*/
static char	*read_input(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	return (line);
}

/*
Exits minishell cleanly after EOF is received at the prompt.
1.	Saves the current last_exit value before clearing shell memory
2.	Prints "exit" on Ctrl-D
3.	Clears line-level allocations from the current loop iteration
4.	Clears shell-level allocations that live for the full program
5.	Exits with the previous command status, cast to an unsigned char
*/
static void	exit_shell(t_shell *shell)
{
	int	status;

	status = shell->last_exit;
	printf("exit\n");
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	exit((unsigned char)status);
}

/*
Runs the interactive minishell prompt loop.
1.	Repeats forever so minishell does not close after one command
2.	Restores prompt signal handling before each readline call
3.	Launches read_input 
4.	If an interruption signal SIGINT is received (Ctrl-C) updates 
	last_exit to 130
5.	Exits cleanly when readline returns NULL from EOF
6.	Processes each input line and frees it before the next prompt
*/
void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_prompt_signals();
		line = read_input();
		if (g_signal == SIGINT)
		{
			shell->last_exit = 130;
			g_signal = 0;
		}
		if (!line)
			exit_shell(shell);
		process_line(line, shell);
		free(line);
	}
}
