/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:00:53 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 14:04:16 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_redir_token(t_shell *shell, t_token **tokens,
	char *value, t_token_type type)
{
	if (!value)
		return (0);
	if (!add_token_back(tokens, create_token(shell, type, value)))
		return (free(value), 0);
	free(value);
	return (1);
}

static void	get_input_redir(char *line, int op, t_token_type *type)
{
	*type = T_REDIR_IN;
	if (line[op + 1] == '<' && line[op + 2] == '<')
		*type = T_HERE_STRING;
	else if (line[op + 1] == '<')
		*type = T_HEREDOC;
	else if (line[op + 1] == '>')
		*type = T_READ_WRITE;
}

static int	get_input_len(char *line, int start, int op)
{
	if (line[op + 1] == '<' && line[op + 2] == '<')
		return (op - start + 3);
	if (line[op + 1] == '<')
		return (op - start + 2);
	if (line[op + 1] == '>')
		return (op - start + 2);
	return (op - start + 1);
}

static int	get_output_len(char *line, int start, int op,
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

int	handle_redir_in(t_shell *shell, char *line, int *i, t_token **tokens)
{
	int				start;
	int				op;
	int				len;
	t_token_type	type;

	start = *i;
	while (ft_isdigit(line[*i]))
		(*i)++;
	op = *i;
	get_input_redir(line, op, &type);
	len = get_input_len(line, start, op);
	*i = op + len - (op - start);
	return (add_redir_token(shell, tokens,
			ft_substr(line, start, len), type));
}

int	handle_redir_out(t_shell *shell, char *line, int *i, t_token **tokens)
{
	int				start;
	int				op;
	int				len;
	t_token_type	type;

	start = *i;
	while (ft_isdigit(line[*i]))
		(*i)++;
	op = *i;
	len = get_output_len(line, start, op, &type);
	*i = op + len - (op - start);
	return (add_redir_token(shell, tokens,
			ft_substr(line, start, len), type));
}
