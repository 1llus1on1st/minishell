/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_marked_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:41:15 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 12:41:18 by mshargan         ###   ########.fr       */
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

static int	copy_double_marked(t_shell *shell, char *str, char **res, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
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

static int	handle_marked_char(t_shell *shell, char *str, char **res, int *i)
{
	if (str[*i] == '\'')
		return (copy_single_marked(shell, str, res, i));
	if (str[*i] == '"')
		return (copy_double_marked(shell, str, res, i));
	if (str[*i] == '$')
		return (expand_unquoted_variable(shell, str, res, i));
	return (append_char(shell, res, str[(*i)++]));
}

char	*expand_marked_word(t_shell *shell, char *str, int *had_quote)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	if (!gc_add(&shell->line_gc, res))
		return (free(res), NULL);
	i = 0;
	*had_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			*had_quote = 1;
		if (!handle_marked_char(shell, str, &res, &i))
			return (NULL);
	}
	return (res);
}
