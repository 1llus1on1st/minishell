/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 12:47:47 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/28 16:58:44 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

int	lexer(t_shell *shell, char *line, t_token **tokens)
{
	int		i;
	char	c;
	
	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		c = line[i];
		if (!line[i])
			break ;
		if (c == '|' && !handle_pipe(shell, line, &i, tokens))
			return (1);
		else if (c == '<' && !handle_redir_in(shell, line, &i, tokens))
			return (1);
		else if (c == '>' && !handle_redir_out(shell, line, &i, tokens))
			return (1);
		else if (c != '|' && c != '<' && c != '>'
					&& !handle_word(shell, line, &i, tokens))
			return (1);
	}
	return (0);
}
