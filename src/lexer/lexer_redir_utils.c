/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:28:41 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:41:47 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_redir_token(t_shell *shell, t_token **tokens,
	char *value, t_token_type type)
{
	if (!value)
		return (0);
	if (!add_token_back(tokens, create_token(shell, type, value)))
		return (free(value), 0);
	free(value);
	return (1);
}

void	get_input_redir(char *line, int op, t_token_type *type)
{
	*type = T_REDIR_IN;
	if (line[op + 1] == '<' && line[op + 2] == '<')
		*type = T_HERE_STRING;
	else if (line[op + 1] == '<')
		*type = T_HEREDOC;
	else if (line[op + 1] == '>')
		*type = T_READ_WRITE;
}

int	get_input_len(char *line, int start, int op)
{
	if (line[op + 1] == '<' && line[op + 2] == '<')
		return (op - start + 3);
	if (line[op + 1] == '<')
		return (op - start + 2);
	if (line[op + 1] == '>')
		return (op - start + 2);
	return (op - start + 1);
}

int	get_output_len(char *line, int start, int op,
	t_token_type *type)
{
	*type = T_REDIR_OUT;
	if (line[op + 1] == '>')
	{
		*type = T_APPEND;
		return (op - start + 2);
	}
	if (line[op + 1] == '|')
		return (op - start + 2);
	return (op - start + 1);
}
