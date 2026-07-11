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

/*
Checks whether a character can continue a variable name.
1.	Accepts letters, digits and underscores
2.	Used after '$' while reading an environment key
*/
int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
Appends one character to an expansion result.
1.	Builds a temporary one-character string
2.	Joins it to the current result
3.	Tracks the new result in line_gc and updates the result pointer
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
Appends a string to an expansion result.
1.	Treats NULL as an empty string for missing environment variables
2.	Joins the string to the current result
3.	Tracks the new result in line_gc and updates the result pointer
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
