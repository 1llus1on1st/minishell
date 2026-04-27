/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:28:13 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/27 15:45:58 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

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

void	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	handle_redir_in(char *line, int *i, t_token **tokens)
{
	if (line[*i + 1] == '<')
	{
		add_token_back(tokens, create_token(T_HEREDOC, "<<"));
		*i += 2;
	}
	else
	{
		add_token_back(tokens, create_token(T_REDIR_IN, "<"));
		(*i)++;
	}
}

void	handle_redir_out(char *line, int *i, t_token **tokens)
{
	if (line[*i + 1] == '>')
	{
		add_token_back(tokens, create_token(T_APPEND, ">>"));
		*i += 2;
	}
	else
	{
		add_token_back(tokens, create_token(T_REDIR_OUT, ">"));
		(*i)++;
	}
}
