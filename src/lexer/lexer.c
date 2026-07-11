/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:51 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 13:58:56 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Moves the lexer index past spaces between tokens.
1.	Skips only spaces and tabs because they separate shell words
2.	Stops on the next real character or the end of the line
*/
static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

/*
Returns the index after an optional file descriptor prefix.
1.	Starts from the current lexer position
2.	Moves past digits used before redirections, like 2> or 0<
3.	Returns the first non-digit index
*/
static int	skip_fd(char *line, int i)
{
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

/*
Checks whether the current token starts with an fd redirection.
1.	Scans leading digits from the current index
2.	Rejects the case where no digit was found
3.	Returns true only when the digits are followed by '<' or '>'
*/
static int	is_fd_redir(char *line, int i)
{
	int	start;

	start = i;
	while (ft_isdigit(line[i]))
		i++;
	if (i == start)
		return (0);
	return (line[i] == '<' || line[i] == '>');
}

/*
Chooses the correct lexer handler for the next token.
1.	Handles normal operators first: pipe, '<' and '>'
2.	Handles fd-prefixed redirections such as 2> and 0<
3.	Sends everything else to the word handler
4.	Returns 0 if the selected handler fails
*/
static int	handle_next_token(t_shell *shell, char *line, int *i,
	t_token **tokens)
{
	char	c;
	int		op;

	c = line[*i];
	op = skip_fd(line, *i);
	if (c == '|')
		return (handle_pipe(shell, i, tokens));
	if (c == '<')
		return (handle_redir_in(shell, line, i, tokens));
	if (c == '>')
		return (handle_redir_out(shell, line, i, tokens));
	if (is_fd_redir(line, *i) && line[op] == '<')
		return (handle_redir_in(shell, line, i, tokens));
	if (is_fd_redir(line, *i) && line[op] == '>')
		return (handle_redir_out(shell, line, i, tokens));
	if (c != '|' && c != '<' && c != '>')
		return (handle_word(shell, line, i, tokens));
	return (1);
}

/*
Converts one input line into a linked list of tokens.
1.	Walks through the line from left to right
2.	Skips whitespace before each token
3.	Stops cleanly if only spaces remain
4.	Delegates token-specific work to handle_next_token
5.	Returns 0 on success and 1 if lexing fails
*/
int	lexer(t_shell *shell, char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (!handle_next_token(shell, line, &i, tokens))
			return (1);
	}
	return (0);
}
