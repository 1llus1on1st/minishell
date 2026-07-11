/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_marked_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:41:30 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 12:45:03 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks whether a character is the internal field-splitting marker.
*/
static int	is_split(char c)
{
	return (c == EXP_SPLIT);
}

/*
Counts how many words exist inside a marked expansion result.
1.	Skips consecutive EXP_SPLIT markers like shell field separators
2.	Counts each non-empty run between split markers as one word
*/
int	marked_word_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		while (is_split(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !is_split(str[i]))
			i++;
	}
	return (count);
}

/*
Measures one word inside a marked expansion result.
1.	Starts at the first character of the word
2.	Stops before the next EXP_SPLIT marker or end of string
*/
static int	marked_word_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && !is_split(str[i + len]))
		len++;
	return (len);
}

/*
Extracts one word from a marked expansion result.
1.	Skips split markers until the requested word index is reached
2.	Copies that word into a new garbage-collected string
3.	Returns NULL when the requested word does not exist
*/
char	*marked_get_word(t_shell *shell, char *str, int index)
{
	int		i;
	int		count;
	char	*word;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		while (is_split(str[i]))
			i++;
		if (str[i] && count++ == index)
		{
			word = ft_substr(str, i, marked_word_len(str, i));
			if (!word)
				return (NULL);
			if (!gc_add(&shell->line_gc, word))
				return (free(word), NULL);
			return (word);
		}
		while (str[i] && !is_split(str[i]))
			i++;
	}
	return (NULL);
}

/*
Adds marked expansion words back into a command argv array.
1.	Preserves a quoted empty result when keep_empty is true
2.	Splits unquoted marked results into separate argv entries
3.	Returns 0 if extracting or adding any word fails
*/
int	add_marked_words(t_shell *shell, t_cmd *cmd, char *marked, int keep_empty)
{
	int		i;
	int		count;
	char	*word;

	count = marked_word_count(marked);
	if (count == 0 && keep_empty)
		return (add_arg(shell, cmd, ""));
	i = 0;
	while (i < count)
	{
		word = marked_get_word(shell, marked, i);
		if (!word || !add_arg(shell, cmd, word))
			return (0);
		i++;
	}
	return (1);
}
