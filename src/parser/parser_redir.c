/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 12:00:00 by mshargan          #+#    #+#             */
/*   Updated: 2026/05/18 12:00:00 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks whether a token type is one of the redirection operators.
1.	Compares the type with input redirection
2.	Compares the type with output redirection
3.	Compares the type with append redirection
4.	Compares the type with heredoc redirection
5.	Returns 1 for redirection types and 0 for all other token types
*/
int	is_redir(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

/*
Adds a redirection node to the end of a command redirection list.
1.	If the list is empty, stores the new redirection as the first node
2.	Otherwise starts from the first redirection in the list
3.	Moves forward until it reaches the last redirection
4.	Links the last redirection to the new redirection
*/
static void	add_redir_back(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*current;

	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	current = *redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

/*
Checks whether a string contains quote characters.
1.	Starts scanning the string from index 0
2.	Handles NULL safely by stopping before reading the string
3.	Returns 1 if it finds a single quote or double quote
4.	Returns 0 if the whole string has no quote characters
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

static int	default_redir_fd(t_token_type type)
{
	if (type == T_REDIR_IN || type == T_HEREDOC)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static int	get_redir_fd(t_token_type type, char *value)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	if (!value || !ft_isdigit(value[0]))
		return (default_redir_fd(type));
	while (ft_isdigit(value[i]))
	{
		fd = fd * 10 + value[i] - '0';
		i++;
	}
	return (fd);
}

static t_redir	*create_redir(t_shell *shell, t_token_type type,
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

int	parse_redir(t_shell *shell, t_token **token, t_cmd *cmd)
{
	t_redir	*redir;

	if (!(*token)->next || (*token)->next->type != T_WORD)
		return (0);
	redir = create_redir(shell, (*token)->type,
			(*token)->value, (*token)->next->value);
	if (!redir)
		return (0);
	add_redir_back(&cmd->redirs, redir);
	*token = (*token)->next;
	return (1);
}
