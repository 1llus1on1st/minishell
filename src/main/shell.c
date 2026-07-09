/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:14:25 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 12:42:49 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
1.	Displays the minishell prompt and waits for user input
2.	Adds non-empty input lines to the readline history
3.	Returns the line read by readline, or NULL if EOF is reached
*/
static char	*read_input(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	return (line);
}

static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = NULL;
	cmds = NULL;
	if (lexer(shell, line, &tokens) != 0)
		return (shell->last_exit = 2, gc_clear(&shell->line_gc));
	if (parser(shell, tokens, &cmds) != 0)
		return (shell->last_exit = 2, gc_clear(&shell->line_gc));
	if (!cmds)
		return (gc_clear(&shell->line_gc));
	if (!expand(shell, cmds))
		return (gc_clear(&shell->line_gc));
	if (!prepare_heredocs(shell, cmds))
	{
		if (g_signal == SIGINT)
			shell->last_exit = 130;
		else
			shell->last_exit = 1;
		g_signal = 0;
		close_heredoc_fds(cmds);
		return (gc_clear(&shell->line_gc));
	}
	shell->last_exit = execute_cmd(shell, cmds);
	close_heredoc_fds(cmds);
	gc_clear(&shell->line_gc);
}

/*
1.	Prints "exit" when minishell receives EOF
2.	Clears the line garbage collector
3.	Clears the shell garbage collector
4.	Exits the program with status 0
*/
static void	exit_shell(t_shell *shell)
{
	printf("exit\n");
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	exit(0);
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
