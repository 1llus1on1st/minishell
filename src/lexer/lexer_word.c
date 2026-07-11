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
1.	Returns 1 for '|', '<' or '>'
2.	Returns 0 for every other character
*/
static int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/*
Checks whether a character is whitespace used to separate tokens.
1.	Returns 1 for spaces and tabs
2.	Returns 0 for every other character
*/
static int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

/*
Skips over a quoted part while measuring a word token.
1.	Stores whether the opening quote is single or double
2.	Moves past the opening quote
3.	Advances until the matching closing quote is found
4.	Returns 0 if the quote is never closed
5.	Moves past the closing quote when the quoted part is valid
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
1.	Measures from the current index until a separator or operator is found
2.	Skips quoted sections so spaces and operators inside quotes stay in the word
3.	Rejects the word if a quote is not closed
4.	Creates a substring for the full word and stores it as T_WORD
5.	Advances the lexer index past the word
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
