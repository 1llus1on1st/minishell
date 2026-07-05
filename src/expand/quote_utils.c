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
