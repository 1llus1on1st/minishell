/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:37:03 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 19:59:00 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Copies the content inside one quoted section without keeping the quote marks.
1.	Stores whether the opening quote is single or double
2.	Moves the input index past the opening quote
3.	Copies characters until the matching closing quote is found
4.	Moves the index past the closing quote when it exists
5.	Returns 0 if appending a character fails, otherwise returns 1
*/
static int	copy_quoted(t_shell *shell, char *str, char **res, int *i)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
	{
		if (!append_char(shell, res, str[(*i)++]))
			return (0);
	}
	if (str[*i] == quote)
		(*i)++;
	return (1);
}

/*
Creates a new string with all quote characters removed.
1.	Starts with an empty result string tracked by the line garbage collector
2.	Loops through each character of the input string
3.	Copies quoted content without copying the quote characters themselves
4.	Copies normal characters directly into the result
5.	Returns the unquoted string or NULL if allocation fails
*/
char	*remove_quotes(t_shell *shell, char *str)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	if (!gc_add(&shell->line_gc, res))
		return (free(res), NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!copy_quoted(shell, str, &res, &i))
				return (NULL);
		}
		else if (!append_char(shell, &res, str[i++]))
			return (NULL);
	}
	return (res);
}
