/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_marked_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:41:30 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 12:41:35 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_split(char c)
{
	return (c == EXP_SPLIT);
}

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

static int	marked_word_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && !is_split(str[i + len]))
		len++;
	return (len);
}

char	*marked_get_word(t_shell *shell, char *str, int index)
{
	int	i;
	int	count;
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
