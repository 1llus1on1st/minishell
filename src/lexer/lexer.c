/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:51 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 11:19:43 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Skips whitespace before the next token in the input line.
1.	Checks the current character at index i
2.	Advances i while the character is a space or tab
3.	Stops when it reaches a non-space character or the end of the line
*/
static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static int	skip_fd(char *line, int i)
{
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

static int	is_fd_redir(char *line, int i)
{
	int	start;

	start = i;
	while (ft_isdigit(line[i]))
		i++;
	if (i == start)
		return (0);
	return (line[i] == '<' || line[i] == '>');
}

int	lexer(t_shell *shell, char *line, t_token **tokens)
{
	int		i;
	char	c;
	int		op;

	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		c = line[i];
		if (!line[i])
			break ;
		op = skip_fd(line, i);
		if (c == '|' && !handle_pipe(shell, &i, tokens))
			return (1);
		else if (c == '<' && !handle_redir_in(shell, line, &i, tokens))
			return (1);
		else if (c == '>' && !handle_redir_out(shell, line, &i, tokens))
			return (1);
		else if (is_fd_redir(line, i) && line[op] == '<'
			&& !handle_redir_in(shell, line, &i, tokens))
			return (1);
		else if (is_fd_redir(line, i) && line[op] == '>'
			&& !handle_redir_out(shell, line, &i, tokens))
			return (1);
		else if (c != '|' && c != '<' && c != '>'
			&& !handle_word(shell, line, &i, tokens))
			return (1);
	}
	return (0);
}
