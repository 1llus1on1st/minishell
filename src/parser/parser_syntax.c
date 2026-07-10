/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 13:56:48 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 15:18:40 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Returns the printable value used in syntax error messages.
1.	Checks whether the token pointer is NULL
2.	Returns "newline" when the parser reached the end unexpectedly
3.	Returns the token value when an actual token caused the error
*/
static char	*token_value(t_token *token)
{
	if (!token)
		return ("newline");
	return (token->value);
}

/*
Prints a parser syntax error for an unexpected token.
1.	Writes the minishell syntax error prefix to stderr
2.	Prints either the token value or "newline"
3.	Closes the error message with a quote and newline
4.	Returns 0 so callers can fail directly from this helper
*/
static int	print_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_value(token), 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

/*
Checks whether a pipe token is valid in its current position.
1.	Rejects a pipe at the beginning of the command line
2.	Rejects a pipe at the end of the command line
3.	Rejects two pipe tokens placed directly next to each other
4.	Prints a syntax error when the pipe is invalid
5.	Returns 1 when the pipe has a command before and after it
*/
static int	check_pipe_syntax(t_token *prev, t_token *current)
{
	if (!prev || !current->next || prev->type == T_PIPE)
		return (print_syntax_error(current));
	return (1);
}

static int	check_redir_syntax(t_token *current)
{
	if (!current->next)
		return (print_syntax_error(NULL));
	if (current->next->type != T_WORD)
		return (print_syntax_error(current->next));
	return (1);
}

/*
Checks the full token list for parser syntax errors.
1.	Keeps track of the previous token while walking through the list
2.	Validates every pipe token with pipe-specific rules
3.	Validates every redirection token with redirection-specific rules
4.	Stops immediately when a syntax error is found
5.	Returns 1 when the whole token list is syntactically valid
*/
int	check_syntax(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
		{
			if (!check_pipe_syntax(prev, tokens))
				return (0);
		}
		else if (is_redir(tokens->type))
		{
			if (!check_redir_syntax(tokens))
				return (0);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}
