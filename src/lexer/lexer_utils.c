/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:47 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 11:55:24 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Creates a new token for the lexer token list.
1.	Allocates memory for a t_token using the line garbage collector
2.	Stores the token type inside the new token
3.	Duplicates the token value so the token owns its own string
4.	Adds the duplicated value to the garbage collector
5.	Initializes next to NULL and returns the completed token
*/
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

/*
Adds a token to the end of the token linked list.
1.	Checks that the new token exists
2.	If the list is empty, makes the new token the first token
3.	Otherwise walks through the list until the last token
4.	Links the last token to the new token
5.	Returns 1 on success and 0 if the new token is NULL
*/
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

/*
Handles a pipe character found by the lexer.
1.	Creates a T_PIPE token with the value "|"
2.	Adds the pipe token to the token list
3.	Moves the input index forward by one character
4.	Returns 1 on success and 0 if token creation or insertion fails
*/
int	handle_pipe(t_shell *shell, int *i, t_token **tokens)
{
	if (!add_token_back(tokens, create_token(shell, T_PIPE, "|")))
		return (0);
	(*i)++;
	return (1);
}

/*
Handles input redirection operators found by the lexer.
1.	Checks if the current character is followed by another '<'
2.	Creates a T_HEREDOC token for "<<"
3.	If there is only one '<', creates a T_REDIR_IN token
4.	Advances the input index by two characters for heredoc or one for normal input redirection
5.	Returns 1 on success and 0 if token creation or insertion fails
*/
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

/*
Handles output redirection operators found by the lexer.
1.	Checks if the current character is followed by another '>'
2.	Creates a T_APPEND token for ">>"
3.	If there is only one '>', creates a T_REDIR_OUT token
4.	Advances the input index by two characters for append or one for normal output redirection
5.	Returns 1 on success and 0 if token creation or insertion fails
*/
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
