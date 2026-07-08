/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 13:56:48 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/08 13:57:25 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*token_value(t_token *token)
{
	if (!token)
		return ("newline");
	return (token->value);
}

static int	print_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_value(token), 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

static int	check_pipe_syntax(t_token *prev, t_token *current)
{
	if (!prev || !current->next || prev->type == T_PIPE)
		return (print_syntax_error(current));
	return (1);
}

static int	check_redir_syntax(t_token *current)
{
	if (!current->next)
		return (print_syntax_error(NULL));
	if (current->next->type != T_WORD)
		return (print_syntax_error(current->next));
	return (1);
}

int	check_syntax(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
		{
			if (!check_pipe_syntax(prev, tokens))
				return (0);
		}
		else if (is_redir(tokens->type))
		{
			if (!check_redir_syntax(tokens))
				return (0);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}