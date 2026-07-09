/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:37:08 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 19:58:52 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Appends one character to an expanding result string.
1.	Builds a temporary one-character string
2.	Joins the current result with that temporary string
3.	Returns 0 if the join allocation fails
4.	Adds the joined string to the line garbage collector
5.	Updates the result pointer to the new joined string
*/
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

/*
Appends a full string to an expanding result string.
1.	Treats a NULL source string as an empty string
2.	Joins the current result with the source string
3.	Returns 0 if the join allocation fails
4.	Adds the joined string to the line garbage collector
5.	Updates the result pointer to the new joined string
*/
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
