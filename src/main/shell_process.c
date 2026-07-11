/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 13:03:59 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/11 12:50:55 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Exits immediately after a syntax error in non-interactive mode.
1.	Checks whether stdin is not connected to an interactive terminal
2.	If it is, leaves interactive mode running so the user can keep typing 
	commands
3.	Clears line-level allocations before exiting non-interactive mode
4.	Clears shell-level allocations before leaving the program
5.	Exits with status 2, the usual status for shell syntax errors
*/
static void	exit_noninteractive_syntax(t_shell *shell)
{
	if (!isatty(STDIN_FILENO))
	{
		gc_clear(&shell->line_gc);
		gc_clear(&shell->shell_gc);
		exit(2);
	}
}

/*
Handles a lexer or parser syntax failure.
1.	Sets last_exit to 2 to mark a syntax error
2.	Exits completely when minishell is running non-interactively (no human input)
3.	Clears the current line garbage collector in interactive mode
4.	Returns 0 so callers can stop processing the current input line
*/
static int	syntax_failure(t_shell *shell)
{
	shell->last_exit = 2;
	exit_noninteractive_syntax(shell);
	gc_clear(&shell->line_gc);
	return (0);
}

/*
Builds the command list from one raw input line.
1.	Runs the lexer to convert the line into tokens
2.	Handles syntax failures on lexer error
3.	Runs the parser to convert tokens into command structures
4.	Handles syntax failures on parser error
5.	Returns 1 only when both lexing and parsing succeed
*/
static int	build_commands(t_shell *shell, char *line,
	t_token **tokens, t_cmd **cmds)
{
	if (lexer(shell, line, tokens) != 0)
		return (syntax_failure(shell));
	if (parser(shell, *tokens, cmds) != 0)
		return (syntax_failure(shell));
	return (1);
}

/*
Handles failure while preparing heredocs for a command line.
1.	Sets last_exit to 130 when the heredoc was interrupted by Ctrl-C
2.	Sets last_exit to 1 for other heredoc preparation failures
3.	Resets the global signal flag after reading it
4.	Closes any heredoc file descriptors that were already opened
5.	Clears line-level allocations before returning to the prompt
*/
static void	heredoc_failure(t_shell *shell, t_cmd *cmds)
{
	if (g_signal == SIGINT)
		shell->last_exit = 130;
	else
		shell->last_exit = 1;
	g_signal = 0;
	close_heredoc_fds(cmds);
	gc_clear(&shell->line_gc);
}

/*
Processes one complete input line from the prompt.
1.	Initializes token and command lists for the current line
2.	Builds commands
3.	Returns early after syntax errors, empty commands
4.	Launches the expander
5.	Returns early on expander error
6.	Prepares heredocs
7.	Executes the command list
8.	Executes commands, closes heredocs and clears line-level allocations
*/
void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = NULL;
	cmds = NULL;
	if (!build_commands(shell, line, &tokens, &cmds))
		return ;
	if (!cmds)
		return (gc_clear(&shell->line_gc));
	if (!expand(shell, cmds))
		return (gc_clear(&shell->line_gc));
	if (!prepare_heredocs(shell, cmds))
		return (heredoc_failure(shell, cmds));
	shell->last_exit = execute_cmd(shell, cmds);
	close_heredoc_fds(cmds);
	gc_clear(&shell->line_gc);
}
