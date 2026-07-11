/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_marked_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:41:15 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:31:31 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Expands one word while marking places where field splitting is allowed.
1.	Removes quote syntax while keeping the protected content
2.	Marks unquoted whitespace from variable values with EXP_SPLIT
3.	Tracks whether quotes appeared so quoted empty words can survive
4.	Returns the marked string used later to build argv or redirection words
*/
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
		if (str[i] == '\'' || str[i] == '"'
			|| (str[i] == '$' && (str[i + 1] == '\''
					|| str[i + 1] == '"')))
			*had_quote = 1;
		if (!handle_marked_char(shell, str, &res, &i))
			return (NULL);
	}
	return (res);
}
