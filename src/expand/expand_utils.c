/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:37:08 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 15:16:13 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	append_char(t_shell *shell, char **res, char c)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(*res, tmp);
	if (!joined)
		return (0);
	if (!gc_add(&shell->line_gc, joined))
		return (free(joined), 0);
	*res = joined;
	return (1);
}

int	append_str(t_shell *shell, char **res, char *str)
{
	char	*joined;

	if (!str)
		str = "";
	joined = ft_strjoin(*res, str);
	if (!joined)
		return (0);
	if (!gc_add(&shell->line_gc, joined))
		return (free(joined), 0);
	*res = joined;
	return (1);
}
