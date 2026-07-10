/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 13:03:59 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 13:04:08 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_noninteractive_syntax(t_shell *shell)
{
	if (!isatty(STDIN_FILENO))
	{
		gc_clear(&shell->line_gc);
		gc_clear(&shell->shell_gc);
		exit(2);
	}
}

static int	syntax_failure(t_shell *shell)
{
	shell->last_exit = 2;
	exit_noninteractive_syntax(shell);
	gc_clear(&shell->line_gc);
	return (0);
}

static int	build_commands(t_shell *shell, char *line,
	t_token **tokens, t_cmd **cmds)
{
	if (lexer(shell, line, tokens) != 0)
		return (syntax_failure(shell));
	if (parser(shell, *tokens, cmds) != 0)
		return (syntax_failure(shell));
	return (1);
}

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