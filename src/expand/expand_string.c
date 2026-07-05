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
