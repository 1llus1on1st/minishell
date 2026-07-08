/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 12:00:00 by mshargan          #+#    #+#             */
/*   Updated: 2026/05/18 12:00:00 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cmd_is_empty(t_cmd *cmd)
{
	if (!cmd->argv && !cmd->redirs)
		return (1);
	return (0);
}

static int	parse_pipe(t_shell *shell, t_cmd **cmds, t_cmd **cmd)
{
	if (cmd_is_empty(*cmd))
		return (0);
	add_cmd_back(cmds, *cmd);
	*cmd = create_cmd(shell);
	if (!*cmd)
		return (0);
	return (1);
}

static int	parse_token(t_shell *shell, t_token **token, t_cmd **cmds,
	t_cmd **cmd)
{
	if ((*token)->type == T_WORD)
		return (add_arg(shell, *cmd, (*token)->value));
	if (is_redir((*token)->type))
		return (parse_redir(shell, token, *cmd));
	if ((*token)->type == T_PIPE)
		return (parse_pipe(shell, cmds, cmd));
	return (0);
}

int	parser(t_shell *shell, t_token *tokens, t_cmd **cmds)
{
	t_cmd	*cmd;

	if (!check_syntax(tokens))
		return (1);
	cmd = create_cmd(shell);
	if (!cmd)
		return (1);
	while (tokens)
	{
		if (!parse_token(shell, &tokens, cmds, &cmd))
			return (1);
		tokens = tokens->next;
	}
	if (cmd_is_empty(cmd))
		return (*cmds != NULL);
	add_cmd_back(cmds, cmd);
	return (0);
}
