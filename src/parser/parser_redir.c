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

int	is_redir(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

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

static t_redir	*create_redir(t_shell *shell, t_token_type type, char *file)
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
	redir = create_redir(shell, (*token)->type, (*token)->next->value);
	if (!redir)
		return (0);
	add_redir_back(&cmd->redirs, redir);
	*token = (*token)->next;
	return (1);
}
