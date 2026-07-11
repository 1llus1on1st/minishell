/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:47 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 14:01:08 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Creates one token node for the lexer token list.
1.	Allocates the token itself with the line garbage collector
2.	Stores the token type and a duplicated copy of its value
3.	Tracks the duplicated value so line cleanup can free it later
4.	Returns NULL if allocation or garbage collection registration fails
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
Appends a token to the end of the token list.
1.	Rejects NULL tokens so failed token creation stops the lexer
2.	Uses the new token as the head when the list is empty
3.	Otherwise walks to the final node and links the new token there
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
Adds a pipe token and moves past it.
1.	Creates a T_PIPE token with the value "|"
2.	Appends it to the lexer token list
3.	Advances the input index by one character
*/
int	handle_pipe(t_shell *shell, int *i, t_token **tokens)
{
	if (!add_token_back(tokens, create_token(shell, T_PIPE, "|")))
		return (0);
	(*i)++;
	return (1);
}
