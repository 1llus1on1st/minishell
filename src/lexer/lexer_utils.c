/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:28:13 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/28 13:08:44 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
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

int	handle_pipe(char *line, int *i, t_token **tokens)
{
	if (!add_token_back(tokens, create_token(T_PIPE, "|")))
			return (0);
		*i++;
}

int	handle_redir_in(char *line, int *i, t_token **tokens)
{
	if (line[*i + 1] == '<')
	{
		if (!add_token_back(tokens, create_token(T_HEREDOC, "<<")))
			return (0);
		*i += 2;
	}
	else
	{
		if (!add_token_back(tokens, create_token(T_REDIR_IN, "<")))
			return (0);
		(*i)++;
	}
	return (1);
}

int	handle_redir_out(char *line, int *i, t_token **tokens)
{
	if (line[*i + 1] == '>')
	{
		if (!add_token_back(tokens, create_token(T_APPEND, ">>")))
			return (0);
		*i += 2;
	}
	else
	{
		if (!add_token_back(tokens, create_token(T_REDIR_OUT, ">")))
			return (0);
		(*i)++;
	}
	return (1);
}
