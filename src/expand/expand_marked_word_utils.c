/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_marked_word_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:31:01 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:41:21 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Copies a single-quoted section into the marked expansion result.
1.	Skips the quote characters themselves
2.	Copies content literally because single quotes disable expansion
*/
static int	copy_single_marked(t_shell *shell, char *str, char **res, int *i)
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
Copies an escaped character during marked expansion.
1.	Skips the backslash when there is a following character
2.	Keeps the final backslash literal when it is the end of the string
*/
static int	copy_escaped_marked(t_shell *shell, char *str, char **res, int *i)
{
	if (str[*i + 1])
	{
		(*i)++;
		if (!append_char(shell, res, str[*i]))
			return (0);
		(*i)++;
		return (1);
	}
	return (append_char(shell, res, str[(*i)++]));
}

/*
Copies a double-quoted section into the marked expansion result.
1.	Allows variable expansion inside the quotes
2.	Handles the escapes that remain special inside double quotes
3.	Does not mark expanded whitespace for splitting because quotes protect it
*/
static int	copy_double_marked(t_shell *shell, char *str, char **res, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '\\' && (str[*i + 1] == '$'
				|| str[*i + 1] == '"' || str[*i + 1] == '\\'))
		{
			if (!copy_escaped_marked(shell, str, res, i))
				return (0);
		}
		else if (str[*i] == '$')
		{
			if (!expand_quoted_variable(shell, str, res, i))
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
Handles the special case where '$' appears before a quote.
1.	Treats $'...' and $"..." as quoted text for this minishell
2.	Otherwise falls back to normal unquoted variable expansion
*/
static int	copy_dollar_quote_marked(t_shell *shell, char *str,
		char **res, int *i)
{
	if (str[*i + 1] == '\'')
	{
		(*i)++;
		return (copy_single_marked(shell, str, res, i));
	}
	if (str[*i + 1] == '"')
	{
		(*i)++;
		return (copy_double_marked(shell, str, res, i));
	}
	return (expand_unquoted_variable(shell, str, res, i));
}

/*
Handles the next character during marked word expansion.
1.	Dispatches quote, escape and variable syntax to specialized helpers
2.	Copies ordinary characters directly into the marked result
*/
int	handle_marked_char(t_shell *shell, char *str, char **res, int *i)
{
	if (str[*i] == '\'')
		return (copy_single_marked(shell, str, res, i));
	if (str[*i] == '"')
		return (copy_double_marked(shell, str, res, i));
	if (str[*i] == '\\')
		return (copy_escaped_marked(shell, str, res, i));
	if (str[*i] == '$')
		return (copy_dollar_quote_marked(shell, str, res, i));
	return (append_char(shell, res, str[(*i)++]));
}
