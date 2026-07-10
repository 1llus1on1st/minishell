/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:14:25 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:17:01 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_input(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	return (line);
}

static void	exit_shell(t_shell *shell)
{
	int	status;

	status = shell->last_exit;
	printf("exit\n");
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	exit((unsigned char)status);
}

/*
Keeps minishell running until EOF is received
1.	Sets up the prompt signal handling before reading input
2.	Reads the user input and updates last_exit after SIGINT
3.	Exits the shell if readline returns NULL
4.	Processes the input line and frees it after execution
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
