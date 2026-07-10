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
		|| type == T_APPEND || type == T_HEREDOC
		|| type == T_READ_WRITE || type == T_HERE_STRING);
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
