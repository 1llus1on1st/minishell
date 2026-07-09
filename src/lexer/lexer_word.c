/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:13:29 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 11:55:53 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks whether a character is a shell operator handled by the lexer.
1.	Compares the character with pipe, input redirection and output redirection
2.	Returns 1 if the character is '|', '<' or '>'
3.	Returns 0 for every other character
*/
static int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/*
Checks whether a character is whitespace used to separate tokens.
1.	Compares the character with space and tab
2.	Returns 1 if the character is a space or tab
3.	Returns 0 for every other character
*/
static int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

/*
Skips over a quoted section inside a word token.
1.	Stores the opening quote character, either single quote or double quote
2.	Moves past the opening quote
3.	Advances j until it finds the matching closing quote
4.	Returns 0 if the end of the line is reached before the quote closes
5.	Moves past the closing quote and returns 1 when the quote is valid
*/
static int	skip_quote(char *line, int start, int *j)
{
	char	quote;

	quote = line[start + *j];
	(*j)++;
	while (line[start + *j] && line[start + *j] != quote)
		(*j)++;
	if (!line[start + *j])
		return (0);
	(*j)++;
	return (1);
}

/*
Reads a complete word token from the input line.
1.	Starts from the current input index and counts the word length with j
2.	Stops when it reaches an operator, a space, a tab or the end of the line
3.	If it finds quotes, skips everything until the matching closing quote
4.	Creates a substring containing the full word
5.	Adds the word as a T_WORD token and advances the input index past it
*/
int	handle_word(t_shell *shell, char *line, int *i, t_token **tokens)
{
	int		j;
	char	*word;

	j = 0;
	while (line[*i + j] && !is_operator(line[*i + j])
		&& !is_space(line[*i + j]))
	{
		if (line[*i + j] == '"' || line[*i + j] == '\'')
		{
			if (!skip_quote(line, *i, &j))
				return (0);
		}
		else
			j++;
	}
	word = ft_substr(line, *i, j);
	if (!word)
		return (0);
	if (!add_token_back(tokens, create_token(shell, T_WORD, word)))
		return (free(word), 0);
	free(word);
	*i += j;
	return (1);
}
