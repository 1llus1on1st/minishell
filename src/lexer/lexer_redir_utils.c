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

/*
Creates and appends a redirection token from a temporary value string.
1.	Rejects NULL values from failed ft_substr calls
2.	Creates the token using the redirection type already selected
3.	Frees the temporary value because create_token duplicates it
*/
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

/*
Chooses the token type for an input redirection operator.
1.	Defaults to normal input redirection
2.	Uses T_HEREDOC for <<
3.	Uses T_HERE_STRING for <<<
4.	Uses T_READ_WRITE for <> because it opens a file for reading and writing
*/
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

/*
Returns the length of an input redirection operator.
1.	Includes any fd prefix between start and op
2.	Returns three operator characters for here-strings
3.	Returns two operator characters for << and <>
4.	Returns one operator character for normal <
*/
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

/*
Chooses the output redirection type and returns the operator length.
1.	Defaults to normal output redirection
2.	Switches to append mode for >>
3.	Keeps >| as a two-character operator for parser compatibility
4.	Includes any fd prefix between start and op in the returned length
*/
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
