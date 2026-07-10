/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_marked_word_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:31:01 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:31:40 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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