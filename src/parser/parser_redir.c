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
Checks whether a token type represents a redirection operator.
1.	Includes the POSIX-style redirections handled by minishell
2.	Also includes project extensions such as <> and <<<
*/
int	is_redir(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_APPEND || type == T_HEREDOC
		|| type == T_READ_WRITE || type == T_HERE_STRING);
}

/*
Adds one redirection to the end of a command redirection list.
1.	Uses the new redirection as the head when the list is empty
2.	Otherwise walks to the last redirection and links the new node there
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
Parses a redirection operator and its target word into the current command.
1.	Requires the next token to be a word because redirections need a target
2.	Creates a t_redir using both the operator text and the target word
3.	Adds the redirection to the command instead of argv
4.	Advances the token pointer over the consumed target word
*/
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
