/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:51 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 11:54:43 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Skips whitespace before the next token in the input line.
1.	Checks the current character at index i
2.	Advances i while the character is a space or tab
3.	Stops when it reaches a non-space character or the end of the line
*/
static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

/*
Converts the input line into a linked list of tokens.
1.	Loops through the input line from left to right
2.	Skips spaces before trying to identify the next token
3.	Detects pipes, input redirections, output redirections and words
4.	Calls the correct handler depending on the current character
5.	Returns 1 if token creation fails, otherwise returns 0 when lexing succeeds
*/
int	lexer(t_shell *shell, char *line, t_token **tokens)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		c = line[i];
		if (!line[i])
			break ;
		if (c == '|' && !handle_pipe(shell, &i, tokens))
			return (1);
		else if (c == '<' && !handle_redir_in(shell, line, &i, tokens))
			return (1);
		else if (c == '>' && !handle_redir_out(shell, line, &i, tokens))
			return (1);
		else if (c != '|' && c != '<' && c != '>'
			&& !handle_word(shell, line, &i, tokens))
			return (1);
	}
	return (0);
}
