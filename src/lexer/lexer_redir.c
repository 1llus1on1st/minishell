/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:00:53 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:29:05 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
