/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 12:47:47 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/27 19:26:16 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

int	lexer(char *line, t_token **tokens)
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
		if (c == '|' && !handle_pipe(line, &i, tokens))
			return (1);
		else if (c == '<' && !handle_redir_in(line, &i, tokens))
			return (1);
		else if (c == '>' && !handle_redir_out(line, &i, tokens))
			return (1);
		else if (c != '|' && c != '<' && c != '>'
					&& !handle_word(line, &i, tokens))
			return (1);
	}
	return (0);
}
