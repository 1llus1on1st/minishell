/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:28:13 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/28 16:50:03 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_shell *shell, t_token_type type, char *value)
{
	t_token	*token;

	token = gc_malloc(&shell->line_gc, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
		return (NULL);
	if (!gc_add(&shell->line_gc, token->value))
		return (free(token->value), NULL);
	token->next = NULL;
	return (token);
}

int	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return (0);
	if (!*tokens)
	{
		*tokens = new_token;
		return (1);
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (1);
}

int	handle_pipe(t_shell *shell, char *line, int *i, t_token **tokens)
{
	if (!add_token_back(tokens, create_token(shell, T_PIPE, "|")))
			return (0);
		*i++;
}

int	handle_redir_in(t_shell *shell, char *line, int *i, t_token **tokens)
{
	if (line[*i + 1] == '<')
	{
		if (!add_token_back(tokens, create_token(shell, T_HEREDOC, "<<")))
			return (0);
		*i += 2;
	}
	else
	{
		if (!add_token_back(tokens, create_token(shell, T_REDIR_IN, "<")))
			return (0);
		(*i)++;
	}
	return (1);
}

int	handle_redir_out(t_shell *shell, char *line, int *i, t_token **tokens)
{
	if (line[*i + 1] == '>')
	{
		if (!add_token_back(tokens, create_token(shell, T_APPEND, ">>")))
			return (0);
		*i += 2;
	}
	else
	{
		if (!add_token_back(tokens, create_token(shell, T_REDIR_OUT, ">")))
			return (0);
		(*i)++;
	}
	return (1);
}
