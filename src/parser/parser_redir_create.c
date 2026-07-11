/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:25:55 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:42:03 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks whether a redirection target contains quote characters.
1.	Used for heredoc delimiters because quoted delimiters disable expansion
2.	Returns 1 as soon as a single or double quote is found
*/
static int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

/*
Returns the default file descriptor for a redirection type.
1.	Input-like redirections default to STDIN_FILENO
2.	Output-like redirections default to STDOUT_FILENO
*/
static int	default_redir_fd(t_token_type type)
{
	if (type == T_REDIR_IN || type == T_HEREDOC
		|| type == T_READ_WRITE || type == T_HERE_STRING)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

/*
Extracts an explicit file descriptor from a redirection operator.
1.	Falls back to the default fd when the operator has no leading digits
2.	Builds the fd number from the digit prefix
3.	Returns -1 on integer overflow so invalid fds can fail later
*/
static int	get_redir_fd(t_token_type type, char *value)
{
	int	i;
	int	fd;
	int	digit;

	if (!value || !ft_isdigit(value[0]))
		return (default_redir_fd(type));
	i = 0;
	fd = 0;
	while (ft_isdigit(value[i]))
	{
		digit = value[i] - '0';
		if (fd > (INT_MAX - digit) / 10)
			return (-1);
		fd = (fd * 10) + digit;
		i++;
	}
	return (fd);
}

/*
Creates a redirection node for a parsed command.
1.	Stores the redirection type and duplicated target file word
2.	Derives the target fd from operators like 2> or 0<
3.	Initializes heredoc bookkeeping before heredocs are prepared
4.	Disables heredoc expansion when the delimiter was quoted
*/
t_redir	*create_redir(t_shell *shell, t_token_type type,
		char *op, char *file)
{
	t_redir	*redir;

	redir = gc_malloc(&shell->line_gc, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (NULL);
	if (!gc_add(&shell->line_gc, redir->file))
		return (free(redir->file), NULL);
	redir->fd = get_redir_fd(type, op);
	redir->heredoc_fd = -1;
	redir->heredoc_expand = 1;
	if (type == T_HEREDOC && has_quotes(file))
		redir->heredoc_expand = 0;
	redir->next = NULL;
	return (redir);
}
