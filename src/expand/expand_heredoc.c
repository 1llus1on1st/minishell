/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:26:46 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/07 21:34:14 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_heredoc_line(t_shell *shell, char *str)
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
		if (str[i] == '$')
		{
			if (!expand_variable(shell, str, &res, &i))
				return (NULL);
		}
		else if (!append_char(shell, &res, str[i++]))
			return (NULL);
	}
	return (res);
}
