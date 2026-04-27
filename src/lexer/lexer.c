/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 12:47:47 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/27 17:38:18 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer(char *line, t_token **tokens)
{
	int		i;
	
	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (line[i] == '|')
		{
			add_token_back(tokens, create_token(T_PIPE, "|"));
			i++;
		}
		else if (line[i] == '<' && !handle_redir_in(line, &i, tokens))
			return (1);
		else if (line[i] == '>' && !handle_redir_out(line, &i, tokens))
			return (1);
		else if (!handle_word(line, &i, tokens))
			return (1);
	}
	return (0);
}
