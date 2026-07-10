/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:51 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 13:58:56 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	handle_next_token(t_shell *shell, char *line, int *i,
	t_token **tokens)
{
	char	c;
	int		op;

	c = line[*i];
	op = skip_fd(line, *i);
	if (c == '|')
		return (handle_pipe(shell, i, tokens));
	if (c == '<')
		return (handle_redir_in(shell, line, i, tokens));
	if (c == '>')
		return (handle_redir_out(shell, line, i, tokens));
	if (is_fd_redir(line, *i) && line[op] == '<')
		return (handle_redir_in(shell, line, i, tokens));
	if (is_fd_redir(line, *i) && line[op] == '>')
		return (handle_redir_out(shell, line, i, tokens));
	if (c != '|' && c != '<' && c != '>')
		return (handle_word(shell, line, i, tokens));
	return (1);
}

int	lexer(t_shell *shell, char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (!handle_next_token(shell, line, &i, tokens))
			return (1);
	}
	return (0);
}
