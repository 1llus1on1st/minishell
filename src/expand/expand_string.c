/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:34:21 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 19:58:55 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Copies content inside single quotes without expanding variables.
1.	Moves the input index past the opening single quote
2.	Copies each character until the closing single quote is found
3.	Keeps dollar signs literal because single quotes disable expansion
4.	Moves the index past the closing quote when it exists
5.	Returns 0 if appending a character fails, otherwise returns 1
*/
static int	copy_single_quotes(t_shell *shell, char *str, char **res, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		if (!append_char(shell, res, str[(*i)++]))
			return (0);
	}
	if (str[*i] == '\'')
		(*i)++;
	return (1);
}

/*
Copies content inside double quotes while still expanding variables.
1.	Moves the input index past the opening double quote
2.	Loops until the closing double quote is found
3.	Expands dollar expressions found inside the double quotes
4.	Copies non-dollar characters directly into the result
5.	Moves past the closing quote and returns 1 when copying succeeds
*/
static int	copy_double_quotes(t_shell *shell, char *str, char **res, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			if (!expand_variable(shell, str, res, i))
				return (0);
		}
		else if (!append_char(shell, res, str[(*i)++]))
			return (0);
	}
	if (str[*i] == '"')
		(*i)++;
	return (1);
}

/*
Handles the next character during normal string expansion.
1.	Sends single-quoted sections to the single quote helper
2.	Sends double-quoted sections to the double quote helper
3.	Expands variables when the current character is '$'
4.	Copies normal characters directly into the result
5.	Returns 0 if the selected helper fails, otherwise returns 1
*/
static int	handle_expand_char(t_shell *shell, char *str, char **res, int *i)
{
	if (str[*i] == '\'')
		return (copy_single_quotes(shell, str, res, i));
	if (str[*i] == '"')
		return (copy_double_quotes(shell, str, res, i));
	if (str[*i] == '$')
		return (expand_variable(shell, str, res, i));
	return (append_char(shell, res, str[(*i)++]));
}

/*
Expands one command string by handling quotes and variables.
1.	Starts with an empty result string tracked by the line garbage collector
2.	Loops through each character of the input string
3.	Removes quote characters while preserving their content
4.	Expands variables outside single quotes and inside double quotes
5.	Returns the expanded string or NULL if any allocation or append fails
*/
char	*expand_string(t_shell *shell, char *str)
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
		if (!handle_expand_char(shell, str, &res, &i))
			return (NULL);
	}
	return (res);
}
