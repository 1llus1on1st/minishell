/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:13:29 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/27 17:02:58 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

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

void	handle_word(char *line, int *i, t_token **tokens)
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
				return ;
		}
		else
			j++;
	}
	word = ft_substr(line, *i, j);
	if (!word)
		return ;
	add_token_back(tokens, create_token(T_WORD, word));
	free(word);
	*i += j;
}
