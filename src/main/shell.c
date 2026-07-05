/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:14:25 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 17:46:14 by mshargan         ###   ########.fr       */
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

// static char	*token_type_to_str(t_token_type type)
// {
// 	if (type == T_WORD)
// 		return ("WORD");
// 	if (type == T_PIPE)
// 		return ("PIPE");
// 	if (type == T_REDIR_IN)
// 		return ("REDIR_IN");
// 	if (type == T_REDIR_OUT)
// 		return ("REDIR_OUT");
// 	if (type == T_APPEND)
// 		return ("APPEND");
// 	if (type == T_HEREDOC)
// 		return ("HEREDOC");
// 	return ("UNKNOWN");
// }

// //Debugger to verify lexer worked correctly
// void	print_tokens(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		printf("%s: %s\n", token_type_to_str(tokens->type), tokens->value);
// 		tokens = tokens->next;
// 	}
// }

static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = NULL;
	cmds = NULL;
	if (lexer(shell, line, &tokens) != 0)
	{
		shell->last_exit = 2;
		gc_clear(&shell->line_gc);
		return ;
	}
	if (parser(shell, tokens, &cmds) != 0)
	{
		shell->last_exit = 2;
		gc_clear(&shell->line_gc);
		return ;
	}
	if (!cmds)
		return (gc_clear(&shell->line_gc));
	if (!expand(shell, cmds))
	{
		shell->last_exit = 2;
		gc_clear(&shell->line_gc);
		return ;
	}
	shell->last_exit = execute_cmd(shell, cmds);
	gc_clear(&shell->line_gc);
	return ;
}

static void	exit_shell(t_shell *shell)
{
	printf("exit\n");
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	exit(0);
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = read_input();
		if (!line)
			exit_shell(shell);
		process_line(line, shell);
		free(line);
	}
}
