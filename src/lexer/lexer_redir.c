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

/*
Handles input-side redirection tokens, with or without an fd prefix.
1.	Remembers where the token starts so the full operator can be copied
2.	Skips an optional fd prefix, such as 0< or 3<<
3.	Chooses between input, heredoc, here-string and read-write token types
4.	Measures the exact operator length, including the fd prefix if present
5.	Adds the complete redirection operator as one token
*/
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

/*
Handles output-side redirection tokens, with or without an fd prefix.
1.	Remembers where the token starts so the full operator can be copied
2.	Skips an optional fd prefix, such as 2> or 1>>
3.	Chooses between output and append token types
4.	Keeps special operators like >| as one redirection token length
5.	Adds the complete redirection operator as one token
*/
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
