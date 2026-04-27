/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 12:47:47 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/27 16:12:14 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lexer(char *line)
{
	int		i;
	t_token	*tokens;
	
	i = 0;
	tokens = NULL;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (line[i] == '|')
		{
			add_token_back(&tokens, create_token(T_PIPE, "|"));
			i++;
		}
		else if (line[i] == '<')
			handle_redir_in(line, &i, &tokens);
		else if (line[i] == '>')
			handle_redir_out(line, &i, &tokens);
		else
			handle_word(line, &i, &tokens);
	}
	return (tokens);
}
